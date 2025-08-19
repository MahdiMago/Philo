#include "philo.h"

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
	usleep(25000);
	pthread_mutex_unlock(&lock);
	}
}

int	main(void)
{
	int i = 0;
	pthread_t thread_1;
	pthread_t thread_2;

	int val = 1;

	pthread_create(&thread_1, NULL, thread_function, &val);
	pthread_create(&thread_2, NULL, thread_function, &val);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	printf("finished !!!!");
	return (0);
}