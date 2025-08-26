
#include "../includes/philo.h"

static int	init_mutex(t_env *env)
{
	int i;

	i = 0;
	env->forks = malloc(sizeof(pthread_mutex_t) * env->count);
	if (!env->forks)
		return (0);
	while (i < env->count)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&env->meal, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&env->writing, NULL) != 0)
		return (0);
	return (1);
}

static int	init_philos(t_env *env)
{
	int i;

	env->philos = malloc(sizeof(t_philo) * env->count);
	if (!env->philos)
		return (0);
	i = 0;
	while (i < env->count)
	{
		env->philos[i].eat_times = 0;
		env->philos[i].pos = i;
		env->philos[i].pos_str = ft_itoa(i);
		env->philos[i].ffork = i;
		env->philos[i].sfork = (i + 1) % env->count;
		env->philos[i].env = env;
		i++;
	}
	return (1);
}

int	init_table(t_env *env)
{
	if (!init_mutex(env))
		return (0);
	if (!init_philos(env))
		return (0);
	return (1);
}
