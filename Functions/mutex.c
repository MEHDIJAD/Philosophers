#include <pthread.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>

typedef struct data_s
{
	int num;
	pthread_mutex_t mutex;

} data_t;

data_t *init_data()
{
	data_t  *data;
	data = malloc(sizeof(data_t));
	if (!data)
		exit(1);
	data->num = 0;
	pthread_mutex_init(&data->mutex, NULL);
	return (data);
}

void free_data(data_t *data)
{
	pthread_mutex_destroy(&data->mutex);
	free(data);
}

void exit_on_error(data_t *data, int exit_code)
{
	free(data);
	exit(exit_code);
}

void *routine(void *arg)
{
    data_t *data;
    int i;

    data = (data_t *)arg;
    i = 0;
    while (i < 10000000)
    {
		pthread_mutex_lock(&data->mutex);
        (data->num)++;
		pthread_mutex_unlock(&data->mutex); //* it unlock thread only after the ++ of num 
        i++;
    }
    return (NULL);  
}



void example()
{
    data_t *data;
    pthread_t t_1;
    pthread_t t_2;

	data = init_data();
    if (pthread_create(&t_1, NULL, routine, data))
        exit_on_error(data, 2);
    if (pthread_create(&t_2, NULL, routine, data))
        exit_on_error(data, 2);
    if (pthread_join(t_1, NULL))
        exit_on_error(data, 3);
    if (pthread_join(t_2, NULL))
        exit_on_error(data, 3);
    printf("Num: %d\n", data->num);
	free_data(data);
}

int main()
{
	example();
}

