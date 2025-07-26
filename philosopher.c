#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		if (check_death(philo->data))
			break ;
		take_forks(philo);
		if (check_death(philo->data))
		{
			release_forks(philo);
			break ;
		}
		philosopher_eat(philo);
		release_forks(philo);
		if (check_death(philo->data))
			break ;
		philosopher_sleep(philo);
		if (check_death(philo->data))
			break ;
		philosopher_think(philo);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	if (philo->data->nb_philos == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meals_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

void	philosopher_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	philosopher_think(t_philo *philo)
{
	print_status(philo, "is thinking");
} 