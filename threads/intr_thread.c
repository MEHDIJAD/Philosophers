
//* Multi-threaded Program

//* pthread_join fuction wait intel a trad is done

//* if we use pthread_join after each thread the process is slower than when we pthread joi all athe the end 
#include <pthread.h>
#include <stdio.h>

void *computation(void *add);

int main(void)
{
    pthread_t thread_1;
    pthread_t thread_2;

    long      value_1 = 1;
    long      value_2 = 2;

    //* for signl_thread; time = 3.943 sec
    //*computation((void *)&value_1);
    //* computation((void *)&value_2);
    
    //* for signl_thread; time = 2.015 sec
    pthread_create(&thread_1, NULL, computation, (void *)&value_1);
    pthread_create(&thread_2, NULL, computation, (void *)&value_2);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    return (0);
}

void *computation(void *add)
{
    long sum = 0;
    long *add_num = (long *)add;

    for (long i = 0; i < 1000000000 ;i++)
       sum += *add_num;
    return (NULL);
}