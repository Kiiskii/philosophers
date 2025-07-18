#include "philos.h"

void	ph_exit(t_data *data, char *msg)
{
	if (msg[0] != '\0')
		ph_putstr_fd(msg, 2);
	data->exit = true;
}

void	ph_cleanup(char *msg, t_philo *philo, t_data *data, size_t i)
{
	ph_destroy_mutexes(data, i, msg);
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
	if (philo)
		free(philo);
}

void	ph_final_cleanup(t_philo *philo)
{
	size_t	i;
	t_data	*data;

	i = 0;
	data = philo->data;
	while (i < data->ph_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (philo)
		free(philo);
	if (data->threads)
		free(data->threads);
	pthread_mutex_destroy(&data->data_lock);
	pthread_mutex_destroy(&data->meal_lock);
}

void	ph_destroy_mutexes(t_data *data, size_t ind, char *msg)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&data->data_lock);
	pthread_mutex_destroy(&data->meal_lock);
	if (ind > 0)
	{
		while (i < ind)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
	}
	ph_exit(data, msg);
}
