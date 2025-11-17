# 📘 Projeto A2 — Ordenação e Análise de Desempenho em C

## 🎯 Objetivo
Este projeto implementa três algoritmos de ordenação em linguagem **C** — **Bubble Sort, Insertion Sort e Quick Sort** — aplicados sobre os dígitos do RGM do aluno e sobre vetores aleatórios.  
O programa mede **comparações, trocas e tempo de execução** de cada método, gerando saída em formato **CSV** para análise comparativa.

---

## 📂 Estrutura do Código
- **Metrics**: estrutura que armazena métricas de execução (`cmp` = comparações, `swp` = trocas).
- **Macros**: `COUNT_CMP` e `COUNT_SWP` para facilitar a contagem de operações.
- **Funções de ordenação**:
  - `bubble_sort`: algoritmo simples O(n²), com otimização para parar se já estiver ordenado.
  - `insertion_sort`: algoritmo O(n²), eficiente para vetores pequenos ou quase ordenados.
  - `quick_sort`: algoritmo O(n log n) médio, usando partição de Lomuto.
- **Funções utilitárias**:
  - `converter_rgm`: converte string do RGM em vetor de dígitos.
  - `imprimir_vetor`: imprime vetor na tela.
  - `rodar_sort`: executa um algoritmo, mede tempo com `clock()` e coleta métricas.
- **main**:
  - Lê o RGM do usuário.
  - Converte para vetor de inteiros.
  - Executa os três métodos de ordenação.
  - Imprime resultados em **CSV** e resumo humano.

---

## ⚙️ Como Compilar e Executar

### Linux/Mac
```bash
gcc -O1 -std=c11 main.c -o ordena
./ordena
