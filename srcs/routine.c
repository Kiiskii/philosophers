#include "philos.h"

void	run_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = arg;
	data = philo->data;
	while (1)
	{
		if (philo->index == data->current_index)
		{
			pthread_mutex_lock(&data->print_lock);
			printf("Thread index: %zu\n", philo->index);
			pthread_mutex_unlock(&data->print_lock);
			data->current_index++;
			pthread_mutex_unlock(&data->index_lock);
			break ;
		}
		pthread_mutex_unlock(&data->index_lock);
		usleep(100);
	}
}
