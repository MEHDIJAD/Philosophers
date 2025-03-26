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

__uint64_t ft_get_time(void)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (__uint64_t)1000) + (tv.tv_usec / 1000));
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
	pthread_mutex_init(&data->death_mutex, NULL);
	data->someone_died = 0;
	data->timestamp_in_ms = ft_get_time();
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
		data->ph[i].index = i + 1; 
		data->ph[i].left_fork = &data->forks[i];
		data->ph[i].right_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		data->ph[i].data = data;
		data->ph[i].last_time_ate = ft_get_time();
		i++;
	}
	return (0);
}
void *ft_ifphilo_die(void *arg)
{
    t_data *data = (t_data *)arg;
    while (1)
    {
        int i = 0;
        while (i < data->number_of_philosophers)
        {
            data->ph[i].time_now = ft_get_time();
            data->ph[i].time_since_last_meal = data->ph[i].time_now - data->ph[i].last_time_ate;

            pthread_mutex_lock(&data->death_mutex);
            if (data->someone_died)
            {
                pthread_mutex_unlock(&data->death_mutex);
                return (NULL);
            }

            if (data->ph[i].time_since_last_meal >= (__uint64_t)data->time_to_die)
            {
                data->someone_died = 1;
                printf("%ld %d died\n", data->ph[i].time_now - data->timestamp_in_ms, data->ph[i].index);
                pthread_mutex_unlock(&data->death_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->death_mutex);
            i++;
        }
        usleep(500);
    }
}


int ft_philo_eat(t_philo *philo)
{
	t_data *data = philo->data;

	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return(-1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	printf("%ld %d has taken a fork\n", (philo->time_now = ft_get_time()) - data->timestamp_in_ms, philo->index);
	printf("%ld %d has taken a fork\n", (philo->time_now = ft_get_time()) - data->timestamp_in_ms, philo->index);
	printf("%ld %d is eating\n", (philo->time_now = ft_get_time()) - data->timestamp_in_ms, philo->index);
	usleep((data->time_to_eat * 1000));
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->last_time_ate = ft_get_time();
	return (0);
}
void *ft_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *data = philo->data;
	__uint64_t now;
	// __uint64_t time_since_last_meal;

	// for(int i = 0; i < data->number_of_times_each_philosopher_must_eat; i++)
	while (1)
	{
		// now = ft_get_time();
		// time_since_last_meal = now - philo->last_time_ate;
		// if (time_since_last_meal >= (__uint64_t)data->time_to_die)
		// {
		// 	if (!data->someone_died)
		// 	{
		// 		data->someone_died = 1;
		// 		printf("%ld %d died\n",(now = ft_get_time()) - data->timestamp_in_ms, philo->index);
		// 	}
		// 	return (NULL);
		// }
		// if (data->someone_died)
		// {

		// 	return (NULL);
		// }
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_mutex);
		if (philo->index % 2 == 0)
			usleep(100);
		if (ft_philo_eat(philo))
			return (NULL);
		// pthread_mutex_lock(philo->left_fork);
		// pthread_mutex_lock(philo->right_fork);
		// printf("%ld %d has taken a fork\n", (now = ft_get_time()) - data->timestamp_in_ms, philo->index);
		// printf("%ld %d has taken a fork\n", (now = ft_get_time()) - data->timestamp_in_ms, philo->index);
		// printf("%ld %d is eating\n", (now = ft_get_time()) - data->timestamp_in_ms, philo->index);
		// usleep((data->time_to_eat * 1000));
		// pthread_mutex_unlock(philo->left_fork);
		// pthread_mutex_unlock(philo->right_fork);
		// philo->last_time_ate = ft_get_time();
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_mutex);
		printf("%ld %d is sleeping\n", (now = ft_get_time()) - data->timestamp_in_ms, philo->index);
		usleep((data->time_to_sleep * 1000));
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_mutex);
		printf("%ld %d is thinking\n", (now = ft_get_time()) - data->timestamp_in_ms, philo->index);
	}
	return (NULL);
}



int ft_start_simulation(t_data *data)
{
	int i;
	pthread_t monitor;

	i = 0;
	if (ft_philos(data))
		return (-1);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->ph[i].th, NULL, ft_routine, &data->ph[i]);
		i++;
	}
	usleep(1000);
	pthread_create(&monitor, NULL, ft_ifphilo_die, (void *)data);		
	i = 0;
	pthread_join(monitor, NULL);
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
		if (ft_start_simulation(&data))
			return (write(2, "Erorr\n",6), 1);
	}
	else
		printf("\033[1;31m❌ Wrong number of arguments! ❌\033[0m\n");
}