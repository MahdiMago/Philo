
#include "../includes/philo.h"

void	state_print(t_philo *philo, char *change, int unlock)
{
	char *timestamp;

	timestamp = ft_itoa(get_time() - philo->env->start_time);
	pthread_mutex_lock(&philo->env->writing);
	if (philo->env->stop_condition && !philo->env->max_eat)
		printf("%s %s %s\n", timestamp, philo->pos_str, change);
	if (unlock)
		pthread_mutex_unlock(&philo->env->writing);
	free(timestamp);
}

void philo_sleep(unsigned long duration, t_env *env)
{
	unsigned long	start;

	start = get_time();
	while (!env->stop_condition)
	{
		if (get_time() - start >= duration)
			break ;
		usleep(env->count * 2);
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->forks[philo->ffork]);
	state_print(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->env->forks[philo->sfork]);
	state_print(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->env->meal);
	state_print(philo, "is eating", 1);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->env->meal);
	philo_sleep(philo->env->time_to_eat, philo->env);
	philo->eat_times++;
	pthread_mutex_unlock(&philo->env->forks[philo->ffork]);
	pthread_mutex_unlock(&philo->env->forks[philo->sfork]);
}
