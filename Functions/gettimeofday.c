#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

void example_1()
{
    struct timeval time;

    if (gettimeofday(&time, NULL))
        return ;
    printf("%ld seconds\n", time.tv_sec);
    printf("%ld microseconds\n", time.tv_usec);
    printf("%ld years passed since 1970\n", time.tv_sec / 60 / 60 / 24 / 365);
}

__uint64_t get_time(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        return (0); 
    return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / 1000)); //* time in milsec
}

void example_2(void)
{
    __uint64_t start_time;
    __uint64_t now;

    start_time = get_time(); //* get the time in milsec 
    usleep(10000); //* sleep for 10.000 usec = 0.01 sec = 10 milsec
    now = get_time(); //* get time now == after 10 milsec time  (in milsec)
    printf("%ld milliseconds passed since the start\n", now - start_time); 
    //* the output will be de defrent between the (time(x - 10 milsec) - (time(x) + 10 milsec)
}
int main()
{
    example_1();
    example_2();
    return (0);
}


