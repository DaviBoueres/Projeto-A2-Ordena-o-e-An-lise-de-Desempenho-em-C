#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar métricas
typedef struct {
    long long cmp;  // comparações
    long long swp;  // trocas
} Metrics;

// Macros para contagem
#define COUNT_CMP(m) (m->cmp++)
#define COUNT_SWP(m) (m->swp++)

// Reset métricas
void reset_metrics(Metrics *m) {
    m->cmp = 0;
    m->swp = 0;
}

/* ===========================================================
 * Bubble Sort
 * =========================================================== */
void bubble_sort(int *v, size_t n, Metrics *m) {
    int trocou;
    for (size_t i = 0; i < n - 1; i++) {
        trocou = 0;
        for (size_t j = 0; j < n - 1 - i; j++) {
            COUNT_CMP(m);
            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                COUNT_SWP(m);
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
}

/* ===========================================================
 * Insertion Sort
 * =========================================================== */
void insertion_sort(int *v, size_t n, Metrics *m) {
    for (size_t i = 1; i < n; i++) {
        int key = v[i];
        size_t j = i;
        while (j > 0) {
            COUNT_CMP(m);
            if (v[j - 1] > key) {
                v[j] = v[j - 1];
                COUNT_SWP(m);
                j--;
            } else break;
        }
        v[j] = key;
        COUNT_SWP(m);
    }
}

/* ===========================================================
 * Quick Sort (Lomuto)
 * =========================================================== */
size_t lomuto_partition(int *v, size_t l, size_t r, Metrics *m) {
    int pivot = v[r];
    size_t i = l;
    for (size_t j = l; j < r; j++) {
        COUNT_CMP(m);
        if (v[j] < pivot) {
            int tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
            COUNT_SWP(m);
            i++;
        }
    }
    int tmp = v[i];
    v[i] = v[r];
    v[r] = tmp;
    COUNT_SWP(m);
    return i;
}

void quick_sort_rec(int *v, size_t l, size_t r, Metrics *m) {
    if (l < r) {
        size_t p = lomuto_partition(v, l, r, m);
        if (p > 0) quick_sort_rec(v, l, p - 1, m);
        quick_sort_rec(v, p + 1, r, m);
    }
}

void quick_sort(int *v, size_t n, Metrics *m) {
    if (n > 0) quick_sort_rec(v, 0, n - 1, m);
}

/* ===========================================================
 * Utilitários
 * =========================================================== */
int* converter_rgm(const char *rgm, size_t *out_n) {
    *out_n = strlen(rgm);
    int *vetor = malloc((*out_n) * sizeof(int));
    for (size_t i = 0; i < *out_n; i++)
        vetor[i] = rgm[i] - '0';
    return vetor;
}

void imprimir_vetor(int *v, size_t n) {
    for (size_t i = 0; i < n; i++) printf("%d", v[i]);
}

double rodar_sort(void (*fn)(int*, size_t, Metrics*), int *v, size_t n, Metrics *m) {
    reset_metrics(m);
    clock_t t0 = clock();
    fn(v, n, m);
    clock_t t1 = clock();
    return 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
}

/* ===========================================================
 * MAIN
 * =========================================================== */
int main() {
    char rgm_str[64];
    printf("Digite seu RGM: ");
    scanf("%63s", rgm_str);

    size_t n;
    int *base = converter_rgm(rgm_str, &n);

    printf("\nCSV (para relatório)\n");
    printf("metodo,N,caso,comparacoes,trocas,tempo_ms\n");

    // Bubble Sort
    int *v1 = malloc(n * sizeof(int));
    memcpy(v1, base, n * sizeof(int));
    Metrics m1;
    double t1 = rodar_sort(bubble_sort, v1, n, &m1);
    printf("bubble,%zu,rgm,%lld,%lld,%.4f\n", n, m1.cmp, m1.swp, t1);
    free(v1);

    // Insertion Sort
    int *v2 = malloc(n * sizeof(int));
    memcpy(v2, base, n * sizeof(int));
    Metrics m2;
    double t2 = rodar_sort(insertion_sort, v2, n, &m2);
    printf("insertion,%zu,rgm,%lld,%lld,%.4f\n", n, m2.cmp, m2.swp, t2);
    free(v2);

    // Quick Sort
    int *v3 = malloc(n * sizeof(int));
    memcpy(v3, base, n * sizeof(int));
    Metrics m3;
    double t3 = rodar_sort(quick_sort, v3, n, &m3);
    printf("quick,%zu,rgm,%lld,%lld,%.4f\n", n, m3.cmp, m3.swp, t3);
    free(v3);

    printf("\nResumo humano:\n");
    printf("Bubble -> Comparações: %lld | Trocas: %lld | Tempo: %.4f ms\n", m1.cmp, m1.swp, t1);
    printf("Insertion -> Comparações: %lld | Trocas: %lld | Tempo: %.4f ms\n", m2.cmp, m2.swp, t2);
    printf("Quick -> Comparações: %lld | Trocas: %lld | Tempo: %.4f ms\n", m3.cmp, m3.swp, t3);

    free(base);
    return 0;
}
