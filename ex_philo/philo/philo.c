#include "philo.h"

int is_valid_number(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	while(*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		str++;
	}
	return (0);
}
int   ft_initialize_data(t_data *data, int ac, char *av[])
{
	int i;

	i = 0;
	if (is_valid_number(av[1]) || is_valid_number(av[2]) || 
	is_valid_number(av[3]) || is_valid_number(av[4]))
		return (-1); 
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		if (is_valid_number(av[5]))
			return (-1);
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	}
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
		return (-1);
	while (i < data->number_of_philosophers)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->timestamp_in_ms = 0;
	data->someone_died = 0;
	return (0);
}
int ft_philos(t_data *data)
{
	int i;

	data->ph = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->ph)
		return(-1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->ph[i].index = i; 
		data->ph[i].left_fork = &data->forks[i];
		data->ph[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		data->ph[i].data = data;
		data->ph[i].last_time_ate = 0;
		data->ph[i].time_now = 0;
		i++;
	}
	return (0);
}

__uint64_t ft_get_time(void)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / 1000));
}

void *ft_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *data = philo->data;
	for(int i = 0; i < data->number_of_times_each_philosopher_must_eat; i++)
	{
		// printf("philo->time_now: %ld\n", philo->time_now);
		// printf("philo->last_time_ate: %ld\n", philo->last_time_ate);
		// printf("deff_wrong:%ld\n", philo->last_time_ate - philo->time_now);
		// printf("deff_right:%ld\n", philo->time_now -philo->last_time_ate);
		// printf("time_to_die: %d\n", data->time_to_die);
		philo->time_now = ft_get_time();
		if (philo->last_time_ate != 0 
			&& philo->time_now - philo->last_time_ate >= (__uint64_t)data->time_to_die)
		{
			if (!data->someone_died)
			{
				data->someone_died = 1;
				printf("timestamp_in_ms %d died\n",philo->index);
				exit(0);
			}
			if (data->someone_died)
				return (NULL);
		}
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("timestamp_in_ms %d has taken a fork\n", philo->index);
		printf("timestamp_in_ms %d has taken a fork\n", philo->index);
		printf("timestamp_in_ms %d is eating\n", philo->index);
		usleep((data->time_to_eat * 1000));
		philo->last_time_ate = ft_get_time();
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("timestamp_in_ms %d is sleeping\n", philo->index);
		usleep((data->time_to_sleep * 1000));
		printf("timestamp_in_ms %d is thinking\n", philo->index);
	}
	return (NULL);
}
int ft_start_sumilation(t_data *data)
{
	int i;

	i = 0;
	if (ft_philos(data))
		return (-1);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->ph[i].th, NULL, ft_routine, &data->ph[i]);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->ph[i].th, NULL);
		i++;
	}

	return (0);
}

int main(int ac , char *av[])
{
	t_data data;

	if (ac == 5 || ac == 6)
	{
		if (ft_initialize_data(&data, ac, av))
			return (write(2, "Erorr\n",6), 1);
		if (ft_start_sumilation(&data))
			return (write(2, "Erorr\n",6), 1);
	}
	else
		printf("\033[1;31m❌ Wrong number of arguments! ❌\033[0m\n");
}