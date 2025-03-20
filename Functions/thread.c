#include <pthread.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>


void *print_hello(void *arg)
{
    int i = 0;

    while (i < 100)
    {
        printf("hello\n");
        i++;
        usleep(10000);
    }
    return (NULL);   
}

void *print_world(void *arg)
{
    int i = 0;

    while (i < 100)
    {
        printf("\t\tworld\n");
        i++;
        usleep(10000);
    }
    return (NULL);   
}

void example_1()
{
    print_hello(NULL);
    print_world(NULL);
}

void example_2()
{
    pthread_t t_1;
    pthread_t t_2;

    if (pthread_create(&t_1, NULL, print_hello, NULL))
        exit(1);
    if (pthread_create(&t_2, NULL, print_world, NULL))
        exit(1);
    if (pthread_join(t_1, NULL));
        exit(1);
    if (pthread_join(t_2, NULL));
        exit(1);
}

void *routine(void *arg)
{
    int *num;
    int i;

    num = (int *)arg;
    i = 0;
    while (i < 10000)
    {
        (*num)++;
        i++;
    }
    return (NULL);  
}



void example_3()
{
    int *num;
    pthread_t t_1;
    pthread_t t_2;
    num = malloc(sizeof(int));
    if (!num)
        exit(1);
    *num = 0;
    if (pthread_create(&t_1, NULL, routine, num))
        exit(1);
    if (pthread_create(&t_2, NULL, routine, num))
        exit(1);
    if (pthread_join(t_1, NULL))
        exit(1);
    if (pthread_join(t_2, NULL))
        exit(1);
    printf("Num: %d\n", *num);
}

int main()
{
    // example_1();
    // example_2();
    example_3();
}

//* to fix the data race we use 