#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int id;
    int tempo;
} Alarme;

void *thread_function(void *arg) {
    Alarme *alarme = (Alarme *)arg;
    sleep(alarme->tempo);
    printf("Alarme %d disparado após %d segundos\n", alarme->id, alarme->tempo);
    free(alarme);
    return NULL;
}

int main(int argc, char *argv[]) {

    pthread_t a_thread[10];
    int tempos[10];
    int n = atoi(argv[1]);

    if (n <= 0 || n > 10) {
        printf("Número de alarmes inválido (1 a 10).\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Defina o tempo de espera do alarme %d: ", i + 1);
        scanf("%d", &tempos[i]);
    }
	
	printf("\n");

    for (int i = 0; i < n; i++) {
        Alarme *dados = malloc(sizeof(Alarme));
        dados->id = i + 1;
        dados->tempo = tempos[i];
        pthread_create(&a_thread[i], NULL, thread_function, dados);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(a_thread[i], NULL);
    }

    printf("Todos os alarmes foram disparados.\n");
    return 0;
}
