#include "philo.h"

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;
	long long	current_time;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(&data->meals_mutex);
			current_time = get_time();
			if (current_time - data->philos[i].last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->dead_mutex);
				data->dead = 1;
				pthread_mutex_unlock(&data->dead_mutex);
				print_status(&data->philos[i], "died");
				pthread_mutex_unlock(&data->meals_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->meals_mutex);
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_data	*data;
	int		i;
	int		all_ate;

	data = (t_data *)arg;
	while (1)
	{
		all_ate = 1;
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(&data->meals_mutex);
			if (data->philos[i].meals_eaten < data->nb_meals)
				all_ate = 0;
			pthread_mutex_unlock(&data->meals_mutex);
			i++;
		}
		if (all_ate)
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}

int	check_death(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_mutex);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (dead);
}

int	check_all_ate(t_data *data)
{
	int	all_ate;

	pthread_mutex_lock(&data->meals_mutex);
	all_ate = data->all_ate;
	pthread_mutex_unlock(&data->meals_mutex);
	return (all_ate);
} 