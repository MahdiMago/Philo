#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 0)
		return (1);
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_mutexes(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	if (init_philos(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	monitor_simulation(&data);
	cleanup(&data);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	else
		data->nb_meals = -1;
	data->start_time = get_time();
	data->dead = 0;
	data->all_ate = 0;
	data->forks = NULL;
	data->philos = NULL;
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->dead_mutex, NULL) != 0
		|| pthread_mutex_init(&data->meals_mutex, NULL) != 0)
	{
		cleanup(data);
		return (1);
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nb_philos;
		data->philos[i].last_meal = get_time();
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			free(data->philos);
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor_simulation(t_data *data)
{
	pthread_t	death_monitor;
	pthread_t	meals_monitor;

	if (pthread_create(&death_monitor, NULL, monitor_death, data) != 0)
		return ;
	if (data->nb_meals > 0)
	{
		if (pthread_create(&meals_monitor, NULL, monitor_meals, data) != 0)
		{
			pthread_join(death_monitor, NULL);
			return ;
		}
		pthread_join(meals_monitor, NULL);
	}
	pthread_join(death_monitor, NULL);
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_join(data->philos[i].thread, NULL);
			i++;
		}
		free(data->philos);
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->meals_mutex);
} 