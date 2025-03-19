#include <unistd.h> 
#include <stdio.h>
#include <sys/time.h>

void    example()
{
    struct timeval start_time;
    struct timeval end_time;
    long   requested_sleep_time;
    long   actual_sleep_time;

    requested_sleep_time = 200 * 1000;  //* 200 milsec = 200 * 1000 = 200,000 usec
    //* 1 milsec = 1000 usec
    gettimeofday(&start_time, NULL);
    usleep(requested_sleep_time);
    gettimeofday(&end_time, NULL);
    actual_sleep_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    printf("Requested sleep time: %ld\n", requested_sleep_time);
    printf("Actual sleep time: %ld\n", actual_sleep_time);
}

int main()
{
    example();

    return (0);
}