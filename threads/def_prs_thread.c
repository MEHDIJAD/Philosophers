#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/wait.h>
#include <sys/types.h>

//* process

// int main(int ac, char *av[])
// {
//     int x = 2;
//     int pid = fork();
//     if (pid == -1)
//         return (perror("fork failed\n"), 1);

//     if (pid == 0)
//         x++;
//     sleep(2);
//     printf("value of x is:%d\n", x);
//     if (pid != 0)
//         wait(NULL);
// }

//* thread

int x = 2;

void *routine()
{
    x++;
    sleep(2);
    printf("value of x is %d\n", x);
    return (NULL);
}

void *routine2()
{
    sleep(2);
    printf("value of x is %d\n", x);
    return (NULL);
}
int main()
{
    pthread_t t_1, t_2;
    
    if (pthread_create(&t_1, NULL, &routine, NULL) != 0)
        return (perror("thread creation failed\n"),1);
    if (pthread_create(&t_2, NULL, &routine2, NULL) != 0)
    return (perror("thread creation failed\n"),1);
    pthread_join(t_1, NULL);
    pthread_join(t_2, NULL);
}

/*
* what did we learn here:
    * if we try to print pid : procces_ex gives 2 deff pid but the thread_ex give one pid
        * we can have muliple threads in one process
    * forking muliplie variables and give the to deff process
    * threads wok with the same variables
    * in process changing a value in a process  change it for that precces only 
    * in thread changing a value changre it for all threads , becouse thay are sharing  
*/

