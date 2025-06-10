#include "philos.h"

void	ph_create_threads(t_data *data, t_philo *philo)
{
	void	*func;
	size_t	i;

	func = run_routine;
	i = 0;
	data->threads = malloc(data->ph_count * sizeof(pthread_t));
	if (!data->threads)
		ph_cleanup(MALLOC_FAIL, philo, data->ph_count);
	pthread_mutex_lock(&data->index_lock);
	while (i < data->ph_count)
	{
		if (pthread_create(&data->threads[i], NULL, func, &philo[i]))
			ph_detach_threads(data, philo, i, THREAD_FAIL);
		i++;
	}
	data->start_ms = ph_time_to_ms();
	pthread_mutex_unlock(&data->index_lock);
}

void	ph_join_threads(t_data *data, t_philo *philo)
{
	size_t	i;

	i = 0;
	(void)philo;
	while (i < data->ph_count)
	{
		if (pthread_join(data->threads[i], NULL))
			ph_detach_threads(data, philo, data->ph_count, THREAD_FAIL);
		i++;
	}
}
