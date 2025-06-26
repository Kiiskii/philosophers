#include "philos.h"

void	ph_create_threads(t_data *data, t_philo *philo)
{
	void	*func;
	size_t	i;

	func = run_routine;
	i = 0;
	data->threads = malloc(data->ph_count * sizeof(pthread_t));
	if (!data->threads)
	{
		ph_cleanup(MALLOC_FAIL, philo, data, data->ph_count);
		return ;
	}
	while (i < data->ph_count)
	{
		if (pthread_create(&data->threads[i], NULL, func, &philo[i]))
		{
			data->exit = true;
			ph_join_threads(data, i);
			ph_cleanup(THREAD_FAIL, philo, data, i);
			return ;
		}
		i++;
	}
}

void	ph_join_threads(t_data *data, size_t ind)
{
	size_t	i;

	i = 0;
	while (i < ind)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}
