#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#define NUM_HILOS 5
#define ITERACIONES 3

char timestamp[64];
int contador = 0;
pthread_mutex_t mutex;  // Mutex para proteger la variable compartida

// Función para obtener una marca de tiempo formateada
void obtener_marca_tiempo(char* buffer, size_t len) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    printf("%ld",tv.tv_sec);
}

void* incrementar_contador(void* arg) {
    int id_hilo = *(int*)arg;  // ID del hilo para depuración
	int suma;

    for (int i = 0; i < ITERACIONES; i++) {
		suma = id_hilo * i;
		obtener_marca_tiempo(timestamp, sizeof(timestamp));
		printf("[%s] Salto del hilo %d = %i\n", timestamp, id_hilo, suma);
        pthread_mutex_lock(&mutex);  // Bloqueo del mutex

        contador += suma;  // Sección crítica
		obtener_marca_tiempo(timestamp, sizeof(timestamp));
        printf("[%s] Hilo %d incrementa contador a %d en iteración %d\n", timestamp, id_hilo, contador, i + 1);

        pthread_mutex_unlock(&mutex);  // Liberación del mutex
		sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t hilos[NUM_HILOS];
    int ids_hilos[NUM_HILOS];
    pthread_mutex_init(&mutex, NULL);  // Inicializar el mutex

    // Crear varios hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        ids_hilos[i] = i + 1;  // Asignar ID único a cada hilo
        pthread_create(&hilos[i], NULL, incrementar_contador, &ids_hilos[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    pthread_mutex_destroy(&mutex);  // Destruir el mutex
    printf("Valor final del contador: %d\n", contador);

    return 0;
}
