#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *routine()
{
    printf("Test from threads\n"); //(1)
    sleep(3);
    printf("Ending thread\n"); //(2)

    return (NULL);
}
//! to prof we have 2 thread executiong in the same time we will have messege 1 tow time then 3 sec sleep than messege 2 two times

int main(int ac, char *av[])
{
    pthread_t t_1, t_2;
    
    if (pthread_create(&t_1, NULL, &routine, NULL) != 0)
        return (perror("thread creation failed\n"),1);
    if (pthread_create(&t_2, NULL, &routine, NULL) != 0)
    return (perror("thread creation failed\n"),1);
    pthread_join(t_1, NULL); //* represent the wait() function for threads
    pthread_join(t_2, NULL);
    
    return (0);
}

/*
* what did we learn here:
    * function pthread_create give 0 on success and -1 on failure 
    * if we creat 2 thread they excut at the same time
*/

