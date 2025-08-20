/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:31:58 by mamagoma          #+#    #+#             */
/*   Updated: 2025/08/20 15:13:11 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int thatOneValue = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int	add_value_f(int add)
{
	thatOneValue += add;
	printf("%d\n", thatOneValue);
	return 0;
}

void	*thread_function(void *value)
{
	int add_value = *(int*)value;
	for (int i = 0; i < (100); i++) {
	pthread_mutex_lock(&lock);
	add_value_f(add_value);
	usleep(2500);
	pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int	main(void)
{
	int i = 0;
	pthread_t thread_1;
	pthread_t thread_2;

	int val = 1;

	time_t time2;

	time2 = get_time_in_ms();

	pthread_create(&thread_1, NULL, thread_function, &val);
	pthread_create(&thread_2, NULL, thread_function, &val);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	printf("finished !!!!\n");

	time_t time;

	time = get_time_in_ms();

	printf("time = %ld\n", time);
	printf("time2 = %ld\n", time2);

	return (0);
}
