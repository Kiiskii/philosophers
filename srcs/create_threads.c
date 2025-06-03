  include "philos.h"

void	ph_create_threads(t_data *data, t_philo *philo)
{
	void	*func;
	size_t	i;

	func = run_routine;
	i = 0;
	data->start_ms = ph_time_to_ms();
	data->threads = malloc(data->ph_count * sizeof(pthread_t));
	if (!data->threads)
		ph_exit(MALLOC_FAIL);
	while (i < data->ph_count)
	{
		if (pthread_create(&data->threads[i], NULL, func, &philo[i]))
			ph_exit(THREAD_FAIL);
		i++;
	}
}

void	ph_join_threads(t_data *data, t_philo *philo)
{
	size_t	i;

	i = 0;
	(void)philo;
	while (i < data->ph_count)
	{
		if (pthread_join(data->threads[i], NULL))
			ph_exit(THREAD_FAIL);
		i++;
	}
}
