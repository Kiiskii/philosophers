#include "philos.h"

void	ph_exit(char *msg)
{
	ph_putstr_fd(msg, 2);
	exit(1);
}

void	ph_detach_threads(t_data *data, t_philo *philo, size_t ind, char *msg)
{
	size_t	i;

	i = 0;
	while (i < ind)
	{
		pthread_detach(data->threads[i]);
		i++;
	}
	ph_cleanup(msg, philo, data->ph_count);
}

void	ph_cleanup(char *msg, t_philo *philo, size_t i)
{
	ph_destroy_mutexes(philo->data, i, msg);
	if (philo)
		free(philo);
}

void	ph_destroy_mutexes(t_data *data, size_t ind, char *msg)
{
	size_t	i;

	i = 0;
	if (data->threads)
		free(data->threads);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->index_lock);
	pthread_mutex_destroy(&data->meal_lock);
	if (ind > 0)
	{
		while (i < ind)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	ph_exit(msg);
}
