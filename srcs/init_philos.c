#include "philos.h"

static void	init_forks(t_data *data, t_philo *tmp, size_t i);

void	ph_init_philos(t_data *data, t_philo **philo)
{
	t_philo	*tmp;
	size_t	i;

	tmp = malloc(data->ph_count * sizeof(t_philo));
	if (!tmp)
	{
		ph_cleanup(MALLOC_FAIL, *philo, data->ph_count);
		return ;
	}
	i = 0;
	while (i < data->ph_count)
	{
		tmp[i].index = i + 1;
		tmp[i].data = data;
		init_forks(data, tmp, i);
		tmp[i].last_meal = data->start_ms;
		tmp[i].meals_eaten = 0;
		i++;
	}
	*philo = tmp;
}

static void	init_forks(t_data *data, t_philo *tmp, size_t i)
{
	tmp[i].r_fork = &data->forks[i];
	if (data->ph_count > 1)
	{
		if (i + 1 == data->ph_count)
			tmp[i].l_fork = &data->forks[0];
		else
			tmp[i].l_fork = &data->forks[i + 1];
	}
	/*
	if (data->ph_count % 2 != 0)
	{
		tmp[i].r_fork = &data->forks[i];
		if (data->ph_count > 1)
		{
			if (i == 0)
				tmp[i].l_fork = &data->forks[data->ph_count - 1];
			else
				tmp[i].l_fork = &data->forks[i - 1];
		}
	}
	else
	{
		tmp[i].r_fork = &data->forks[i];
		if (i + 1 == data->ph_count)
			tmp[i].l_fork = &data->forks[0];
		else
			tmp[i].l_fork = &data->forks[i + 1];
	}
	*/
}
