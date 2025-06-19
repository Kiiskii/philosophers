#include "philos.h"

static void	init_fork_mutexes(t_data *data);

void	ph_init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL))
	{
		ph_exit(data, INIT_PRINT_LOCK);
		return ;
	}
	// if (pthread_mutex_init(&data->index_lock, NULL))
	// {
	// 	pthread_mutex_destroy(&data->print_lock);
	// 	ph_exit(data, INIT_PRINT_LOCK);
	// 	return ;
	// }
	// if (pthread_mutex_init(&data->meal_lock, NULL))
	// {
	// 	pthread_mutex_destroy(&data->print_lock);
	// 	pthread_mutex_destroy(&data->index_lock);
	// 	ph_exit(data, INIT_MEAL_LOCK);
	// 	return ;
	// }
	init_fork_mutexes(data);
}

static void	init_fork_mutexes(t_data *data)
{
	size_t	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->ph_count);
	if (!data->forks)
		ph_destroy_mutexes(data, 0, MALLOC_FAIL);
	i = 0;
	while (i < data->ph_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			ph_destroy_mutexes(data, i - 1, INIT_FORK_MUTEX);
		i++;
	}
}
