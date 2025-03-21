#include <pthread.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int mails = 0;

void* routine() {
    for (int i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t th[4];
    int i;
    
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 4; i++)
    {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0)
        {
            perror("Failed to creat threa");
            return (1);
        }
        printf("thread %d has started\n", i);
    }
    for(i = 0; i < 4; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to creat thread");
            return (1);
        }
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;

}