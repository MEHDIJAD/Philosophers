#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *myturn(void *arg)
{
    for (int i = 0; i < 8; i++)
    {
        sleep(1);
        printf("My turn [%d]\n", i);
    }

    return (NULL);   
}

void yourturn()
{
    for (int i = 0; i < 8; i++)
    {
        sleep(2);
        printf("Your turn [%d]\n", i);
    }
    
}
int main()
{
    pthread_t t_1;

    pthread_create(&t_1, NULL, myturn, NULL);
    yourturn();
    pthread_join(t_1, NULL); //* this will wait() main process intell thread function fnish  

}

//* we get ony the output from Myturn function becaus
// we need to return from function 1 to enter fuction 2 
// if we use thread we can run them 2 in the same time 