#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Matrizes globais
int **A, **B, **C;
int linhasA, colunasA, colunasB;

// Estrutura para passar os índices da célula C[i][j]
typedef struct {
    int linha;
    int coluna;
} DadosCelula;

// Cada thread calcula um elemento da matriz C
void *calcula_celula(void *arg) {
    DadosCelula *dados = (DadosCelula *)arg;
    int i = dados->linha;
    int j = dados->coluna;

    C[i][j] = 0;

    // Faz a multiplicação da linha de A pela coluna de B
    for (int k = 0; k < colunasA; k++) {
        C[i][j] += A[i][k] * B[k][j];
    }

    free(dados);
    return NULL;
}

int main() {
    printf("Informe o número de linhas da matriz A: ");
    scanf("%d", &linhasA);

    printf("Informe o número de colunas da matriz A (e linhas da B): ");
    scanf("%d", &colunasA);

    printf("Informe o número de colunas da matriz B: ");
    scanf("%d", &colunasB);

    // Alocação das matrizes A, B e C
    A = malloc(linhasA * sizeof(int *));
    B = malloc(colunasA * sizeof(int *));
    C = malloc(linhasA * sizeof(int *));
    for (int i = 0; i < linhasA; i++) {
        A[i] = malloc(colunasA * sizeof(int));
        C[i] = malloc(colunasB * sizeof(int));
    }
    for (int i = 0; i < colunasA; i++) {
        B[i] = malloc(colunasB * sizeof(int));
    }

    // Entrada de dados da matriz A
    printf("\nDigite os valores da matriz A (%dx%d):\n", linhasA, colunasA);
    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasA; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    // Entrada de dados da matriz B
    printf("\nDigite os valores da matriz B (%dx%d):\n", colunasA, colunasB);
    for (int i = 0; i < colunasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            printf("B[%d][%d] = ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    // Criação de uma thread para cada célula da matriz C
    pthread_t threads[linhasA][colunasB];

    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            DadosCelula *dados = malloc(sizeof(DadosCelula));
            dados->linha = i;
            dados->coluna = j;
            pthread_create(&threads[i][j], NULL, calcula_celula, dados);
        }
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Exibe a matriz C resultante
    printf("\nMatriz Resultado C (%dx%d):\n", linhasA, colunasB);
    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Libera a memória
    for (int i = 0; i < linhasA; i++) {
        free(A[i]);
        free(C[i]);
    }
    for (int i = 0; i < colunasA; i++) {
        free(B[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}

