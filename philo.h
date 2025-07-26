#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	int				meals_eaten;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	long long		start_time;
	int				dead;
	int				all_ate;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meals_mutex;
	t_philo			*philos;
}	t_data;

// Main functions
int			main(int argc, char **argv);
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_data *data);
int			init_mutexes(t_data *data);
void		cleanup(t_data *data);

// Philosopher functions
void		*philosopher_routine(void *arg);
void		philosopher_eat(t_philo *philo);
void		philosopher_sleep(t_philo *philo);
void		philosopher_think(t_philo *philo);
void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);

// Utility functions
long long	get_time(void);
void		ft_usleep(long long time);
int			ft_atoi(const char *str);
int			check_args(int argc, char **argv);
void		print_status(t_philo *philo, char *status);

// Monitoring functions
void		monitor_simulation(t_data *data);
void		*monitor_death(void *arg);
void		*monitor_meals(void *arg);
int			check_death(t_data *data);
int			check_all_ate(t_data *data);

#endif 