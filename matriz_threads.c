#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Matrizes globais
int **A, **B, **C;
int m, k, n;

// Struct para passar dados para cada thread
typedef struct {
    int i; // linha de C
    int j; // coluna de C
} ThreadData;

// Cada thread calcula um único elemento C[i][j]
void *calcular_elemento(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int i = data->i;
    int j = data->j;

    C[i][j] = 0;
    for (int t = 0; t < k; t++) {
        C[i][j] += A[i][t] * B[t][j];  // multiplicação de linha por coluna
    }

    free(data);  // libera memória alocada para os dados da thread
    return NULL;
}

int main() {
    printf("Digite as dimensões das matrizes (m k n): ");
    scanf("%d %d %d", &m, &k, &n);

    // Alocação dinâmica das matrizes A, B e C
    A = malloc(m * sizeof(int *));
    B = malloc(k * sizeof(int *));
    C = malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) A[i] = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) B[i] = malloc(n * sizeof(int));
    for (int i = 0; i < m; i++) C[i] = malloc(n * sizeof(int));

    // Leitura dos elementos da matriz A
    printf("Digite os elementos da matriz A (%dx%d):\n", m, k);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < k; j++)
            scanf("%d", &A[i][j]);

    // Leitura dos elementos da matriz B
    printf("Digite os elementos da matriz B (%dx%d):\n", k, n);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    // Criação de uma thread para cada elemento de C
    pthread_t threads[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ThreadData *data = malloc(sizeof(ThreadData));
            data->i = i;
            data->j = j;
            pthread_create(&threads[i][j], NULL, calcular_elemento, data);
        }
    }

    // Espera todas as threads finalizarem
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            pthread_join(threads[i][j], NULL);

    // Impressão da matriz resultante C
    printf("\nMatriz C (produto de A x B):\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    // Liberação de memória
    for (int i = 0; i < m; i++) free(A[i]);
    for (int i = 0; i < k; i++) free(B[i]);
    for (int i = 0; i < m; i++) free(C[i]);
    free(A); free(B); free(C);

    return 0;
}
