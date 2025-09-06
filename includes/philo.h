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

struct s_env;

typedef struct s_philo
{
	int				eat_times;
	int				pos;
	char			*pos_str;
	int				ffork;
	int				sfork;
	unsigned long	last_eat;
	struct s_env	*env;
	pthread_t		thread_id;
}				t_philo;

typedef struct s_env
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count_max;
	unsigned long	start_time;
	int				stop_condition;
	int				max_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	writing;
}				t_env;


unsigned long	get_time(void);
int		add_value_f(int add);
void	*thread_function(void *value);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_isint(const char *nptr);
int		init_table(t_env *env);
void	state_print(t_philo *philo, char *change, int unlock);
void	philo_sleep(unsigned long duration, t_env *env);
int		start_threads(t_env *env);
void	philo_eat(t_philo *philo);

#endif
