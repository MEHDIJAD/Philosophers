#include <pthread.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *roll_dice(void *arg)
{
    int value = rand() % 6 + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    printf("thread result: %p\n", result);
    return ((void *)result);
}
int main()
{
    pthread_t th;
    int *res;

    srand(time(NULL));
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
        return 1;
    }
    if (pthread_join(th, (void **)&res) != 0) {
        return 2;
    }
    printf("man result: %p\n", res);
    printf("Result:%d\n", *res);
    free(res);
}

//! we can't return a refrence to a local variable because it will be deallocated in the scop of function
//! it is on the stack ==> we need to dynamecly allocate