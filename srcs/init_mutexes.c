#include "philos.h"

void	ph_init_mutexes(t_data *data)
{
	size_t	i;

	if (pthread_mutex_init(&data->print_lock, NULL))
		ph_exit(INIT_PRINT_LOCK);
	if (pthread_mutex_init(&data->index_lock, NULL))
	{
		pthread_mutex_destroy(&data->print_lock);
		ph_exit(INIT_INDEX_LOCK);
	}
	if (pthread_mutex_init(&data->meal_lock, NULL))
	{
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->index_lock);
		ph_exit(INIT_MEAL_LOCK);
	}
	data->current_index = 1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->ph_count);
	if (!data->forks)
		ph_destroy_mutexes(data, 0, MALLOC_FAIL);
	i = 0;
	while (i < data->ph_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			ph_destroy_mutexes(data, i, INIT_FORK_MUTEX);
		i++;
	}
}
