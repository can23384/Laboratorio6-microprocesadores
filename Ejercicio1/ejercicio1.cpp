#include <iostream>
#include <pthread.h>
#include <vector>

struct FibonacciParams {
    int n;
    std::vector<unsigned long long> fibonacci_sequence;
    unsigned long long sum;
};

void* calculate_fibonacci(void* params) {
    FibonacciParams* fib_params = (FibonacciParams*)params;
    int n = fib_params->n;

    fib_params->fibonacci_sequence.resize(n + 1);
    fib_params->fibonacci_sequence[0] = 0;
    if (n > 0) {
        fib_params->fibonacci_sequence[1] = 1;
    }

    for (int i = 2; i <= n; ++i) {
        fib_params->fibonacci_sequence[i] = fib_params->fibonacci_sequence[i - 1] + fib_params->fibonacci_sequence[i - 2];
    }

    fib_params->sum = 0;
    for (int i = 0; i <= n; ++i) {
        fib_params->sum += fib_params->fibonacci_sequence[i];
    }

    pthread_exit(0);
    return NULL;
}

int main() {
    int n;

    do {
        printf("Ingrese un numero entre 0 y 93: ");
        scanf("%d", &n);
    } while (n < 0 || n > 93);

    FibonacciParams fib_params;
    fib_params.n = n;

    pthread_t fib_thread;
    pthread_create(&fib_thread, NULL, calculate_fibonacci, (void*)&fib_params);

    pthread_join(fib_thread, NULL);

    printf("\nSerie de Fibonacci hasta F%d:\n", n);
    for (int i = 0; i <= n; ++i) {
        printf("F%d = %llu\n", i, fib_params.fibonacci_sequence[i]);
    }

    printf("\nLa suma total de los numeros de Fibonacci es: %llu\n", fib_params.sum);

    return 0;
}