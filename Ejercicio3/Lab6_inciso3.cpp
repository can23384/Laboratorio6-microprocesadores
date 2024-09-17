#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define HilosMax 100

struct parametros {
    int id;
    int n;
    double resultado;
};


// Función Calcular terminos
void* calcularTermino(void* arg) {
    struct parametros* p = (struct parametros*) arg;
    p->resultado = pow(-1, p->n + 1) / (double)p->n;
// impresión de cada hilo y su Resultado.Hilo %d.|
    printf("Hilo %d. Calculando n = %d.\n        Resultado = %.6f\n", p->id, p->n, p->resultado);
    pthread_exit(NULL);
    return NULL;
}

int main() {
    // Identificadores de hilos
    pthread_t hilos[HilosMax];
    //Parametros para cada hilo
    struct parametros params[HilosMax];
    int maxN;
    double suma = 0.0;

    printf("Ingrese valor maximo de n: ");
    scanf("%d", &maxN);

// Creacion de hilos
    for (int i = 1; i <= maxN; i++) {
        params[i].id = i;
        params[i].n = i;
        pthread_create(&hilos[i], NULL, calcularTermino, (void*)&params[i]);
    }

    // Esperar a todos los hilos + Suma de todos los resultados de todos los hilos
    for (int i = 1; i <= maxN; i++) {
        // Implementación de parame... por pthread_join
        pthread_join(hilos[i], NULL);
        suma += params[i].resultado;
    }

    printf("\nLa Suma total de la serie: %.6f\n", suma);
    return 0;
}
