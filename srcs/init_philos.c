#include "philos.h"

void	ph_init_philos(t_data *data, t_philo **philo)
{
	t_philo *tmp;
	size_t	i;

	tmp = malloc(data->ph_count * sizeof(t_philo));
	if (!tmp)
		ph_exit(MALLOC_FAIL);
	i = 0;
	while (i < data->ph_count)
	{
		tmp[i].index = i + 1;
		tmp[i].data = data;
		i++;
	}
	*philo = tmp;
}
