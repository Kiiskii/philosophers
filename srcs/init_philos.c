#include "philos.h"

void	ph_init_philos(t_data *data, t_philo **philo)
{
	t_philo *tmp;
	size_t	i;

	tmp = malloc(data->ph_count * sizeof(t_philo));
	if (!tmp)
		ph_cleanup(MALLOC_FAIL, *philo, data->ph_count);
	i = 0;
	while (i < data->ph_count)
	{
		tmp[i].index = i + 1;
		tmp[i].data = data;
		tmp[i].l_fork = &data->forks[i];
		tmp[i].r_fork = &data->forks[(i + 1) % data->ph_count];
		tmp[i].last_meal = ph_time_to_ms();
		i++;
	}
	*philo = tmp;
}
