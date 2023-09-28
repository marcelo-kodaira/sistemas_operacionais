#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h> // Incluímos a biblioteca para usar mutexes

// 64kB stack
#define FIBER_STACK 1024 * 64

struct c {
    int saldo;
};

typedef struct c conta;

conta from, to;
int valor;

// Mutexes para controlar o acesso às contas
pthread_mutex_t from_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t to_mutex = PTHREAD_MUTEX_INITIALIZER;

// A função de transferência agora aceita um argumento de thread
void* transferencia(void* arg)
{
    // Obtemos o valor da conta a partir do argumento
    int valor_transferido = *((int*)arg);

    // Bloqueamos os mutexes para garantir acesso exclusivo às contas
    pthread_mutex_lock(&from_mutex);
    pthread_mutex_lock(&to_mutex);

    // Verificamos se a conta 'from' tem saldo suficiente para a transferência
    if (from.saldo >= valor_transferido)
    {
        from.saldo -= valor_transferido;
        to.saldo += valor_transferido;
    }

    // Liberamos os mutexes após a transferência
    pthread_mutex_unlock(&to_mutex);
    pthread_mutex_unlock(&from_mutex);

    printf("Transferência de %d concluída com sucesso!\n", valor_transferido);
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);

    return NULL;
}

int main()
{
    void* stack;
    pid_t pid;
    int i;

    // Allocate the stack
    stack = malloc(FIBER_STACK);
    if (stack == 0)
    {
        perror("malloc: could not allocate stack");
        exit(1);
    }

    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;

    printf("Transferindo 10 para a conta c2\n");
    valor = 10;

    // Inicializamos as threads
    pthread_t threads[10];
    int valores_transferencia[10];

    for (i = 0; i < 10; i++)
    {
        valores_transferencia[i] = valor;
        if (pthread_create(&threads[i], NULL, transferencia, &valores_transferencia[i]) != 0)
        {
            perror("pthread_create");
            exit(2);
        }
    }

    // Aguardamos o término das threads
    for (i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Free the stack
    free(stack);

    printf("Transferências concluídas e memória liberada.\n");
    return 0;
}
