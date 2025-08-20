/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:31:51 by mamagoma          #+#    #+#             */
/*   Updated: 2025/08/20 21:23:45 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_PHILO 250

typedef struct s_philosopher
{
	int		id;
	int		meals_eaten;
	time_t	last_meal;
}	t_philosopher;

typedef struct s_table
{
	time_t			start_time;
	pthread_mutex_t	fork[MAX_PHILO];
}	t_table;

time_t	get_time_in_ms(void);
int		add_value_f(int add);
void	*thread_function(void *value);
int		ft_atoi(const char *str);
bool	check_argument(int ac, char **av);
int		error_return(void);

#endif
