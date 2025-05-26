#include "philos.h"

void	run_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	size_t	i;

	philo = arg;
	data = philo->data;
	i = 0;
	while (i < data->ph_count)
	{
		printf("Thread index: %d\n", philo->index);
		i++;
	}
}
