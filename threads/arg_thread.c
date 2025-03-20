#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


void *myturn(void *arg)
{
    int *iptr = (int *)malloc(sizeof(int));
    *iptr = 5;

    for (int i = 0; i < 8; i++)
    {
        sleep(1);
        printf("My turn [%d] [%d]\n", i, *iptr);
        (*iptr)++;
    }

    return (iptr);   
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
    int *res;

    pthread_create(&t_1, NULL, myturn, NULL); //* NULL or arg
    yourturn();
    pthread_join(t_1, (void *)&res); //* arg 
    printf("thread is done: *re=%d\n", *res);

}

//* we can pass an argument to pthread_create (arg 4) or we can allocated within the thread funtion and return it 
//* pthread_joid second argement takes the return  arg of pthread_creat !! 