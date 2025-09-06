
#include "../includes/philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->pos % 2 == 0 && philo->env->count > 1)
		philo_sleep(50, philo->env);
	while (!philo->env->stop_condition && !philo->env->max_eat)
	{
		philo_eat(philo);
		state_print(philo, "is sleeping", 1);
		philo_sleep(philo->env->time_to_sleep, philo->env);
		state_print(philo, "is thinking", 1);
	}
	return (NULL);
}

static void	free_threads(t_env *env)
{
	int	i;

	if (env->count == 1)
		pthread_detach(env->philos[0].thread_id);
	else
	{
		i = -1;
		while (++i < env->count)
			pthread_join(env->philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < env->count)
		pthread_mutex_destroy(&env->forks[i]);
	pthread_mutex_unlock(&env->writing);
	pthread_mutex_destroy(&env->writing);
	pthread_mutex_destroy(&env->meal);
	i = -1;
	while (++i < env->count)
		free(env->philos[i].pos_str);
	free(env->philos);
	free(env->forks);
}

static void	monitor(t_env *env)
{
	int	i;

	while (!env->max_eat)
	{
		i = -1;
		while (++i < env->count)
		{
			pthread_mutex_lock(&env->meal);
			if ((get_time() - env->philos[i].last_eat) > (unsigned long)env->time_to_die)
			{
				env->stop_condition = 1;
				state_print(&env->philos[i], "died", 1);
			}
			pthread_mutex_unlock(&env->meal);
		}
		if (env->stop_condition)
			break ;
		i = 0;
		while (i < env->count && env->eat_count_max
			&& env->philos[i].eat_times >= env->eat_count_max)
			i++;
		env->max_eat = (i == env->count);
	}
}

int	start_threads(t_env *env)
{
	int	i;

	i = -1;
	env->start_time = get_time();
	while (++i < env->count)
	{
		env->philos[i].last_eat = get_time();
		if (pthread_create(&env->philos[i].thread_id,
			NULL, routine, &env->philos[i]) != 0)
			return (0);
	}
	monitor(env);
	free_threads(env);
	return (1);
}
