#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Fazer Multiplicação de matrizes
int **A, **B, **C;
int linhasA, colunasA, colunasB;

/
typedef struct {
    int linha;
    int coluna;
} DadosCelula;


void *calcula_celula(void *arg) {
    DadosCelula *dados = (DadosCelula *)arg;
    int i = dados->linha;
    int j = dados->coluna;

    C[i][j] = 0;

    
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

    
    printf("\nDigite os valores da matriz A (%dx%d):\n", linhasA, colunasA);
    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasA; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    
    printf("\nDigite os valores da matriz B (%dx%d):\n", colunasA, colunasB);
    for (int i = 0; i < colunasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            printf("B[%d][%d] = ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    
    pthread_t threads[linhasA][colunasB];

    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            DadosCelula *dados = malloc(sizeof(DadosCelula));
            dados->linha = i;
            dados->coluna = j;
            pthread_create(&threads[i][j], NULL, calcula_celula, dados);
        }
    }

    
    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            pthread_join(threads[i][j], NULL);
        }
    }

    
    printf("\nMatriz Resultado C (%dx%d):\n", linhasA, colunasB);
    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    
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

