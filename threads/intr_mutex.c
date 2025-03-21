#include <pthread.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
    // read mails
    // increment 
    // write mails   
}

int main()
{
    pthread_t t_1, t_2;
    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&t_1, NULL, &routine, NULL) != 0)
        return (1);
    if (pthread_create(&t_2, NULL, &routine, NULL) != 0)
        return (2);
    if (pthread_join(t_1, NULL) != 0)
        return (3);
    if (pthread_join(t_2, NULL) != 0)
        return (4);
    pthread_mutex_destroy(&mutex);
    printf("N:%d\n", mails);

    
}
