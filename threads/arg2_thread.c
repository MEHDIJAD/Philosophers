#include <pthread.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>

/*
* The prob: create 10 threads, each taking a unique prime from 
* the primes array and print it on the sceen.
*/

int primes[10] = {2, 3, 5, 7, 11, 13, 19, 23, 29};

void *routine(void *arg)
{
    int index = *(int *)arg;
    printf("%d ", primes[index]);
    free(arg);
}

int main()
{
    pthread_t th[10];

    for(int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, routine, a) != 0){
            perror("failed to creat thread\n");
        }
    }
    for(int i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0){
            perror("failed to join thread\n");
        }
    }
    return (0);
}