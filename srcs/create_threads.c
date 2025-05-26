#include "philos.h"

void	create_threads(t_data *data, t_philo *philo)
{
	void	*func;
	size_t	i;

	func = run_routine;
	i = 0;
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
