/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:19:57 by mamagoma          #+#    #+#             */
/*   Updated: 2025/08/20 21:28:57 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "includes/philo.h"

static int	check_param(int argc, char **argv, t_env *env)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (!ft_isint(argv[i]))
			return (0);
		if (ft_atoi(argv[i]) < 0)
			return (0);
	}
	env->count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->eat_count_max = ft_atoi(argv[5]);
	else
		env->eat_count_max = 0;
	if (env->count < 0 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->eat_count_max < 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_env	env;
	
	env.max_eat = 0;
	env.stop_condition = 0;
	if (!check_param(argc, argv, &env))
		printf("Error\n");
	if (!init_table(&env))
		printf("Error of initialization");
	if (!start_threads(&env))
		printf("Error while making threads");
}
