#include "philos.h"

static void	init_fork_mutexes(t_data *data);

void	ph_init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->data_lock, NULL))
	{
		ph_exit(data, INIT_DATA_LOCK);
		return ;
	}
	init_fork_mutexes(data);
}

static void	init_fork_mutexes(t_data *data)
{
	size_t	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->ph_count);
	if (!data->forks)
	{
		ph_destroy_mutexes(data, 0, MALLOC_FAIL);
		return ;
	}
	i = 0;
	while (i < data->ph_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			ph_destroy_mutexes(data, i, INIT_FORK_MUTEX);
			free(data->forks);
			return ;
		}
		i++;
	}
}
