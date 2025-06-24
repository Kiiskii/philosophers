#include "philos.h"

static size_t	is_philo_full(t_data *data, t_philo *philo);
static size_t	is_philo_dead(t_data *data, t_philo *philo);

void	ph_monitor(t_data *data, t_philo *philo)
{
	while (data->start_ms > ph_time_to_ms())
		usleep(500);
	while (1)
	{
		if (is_philo_dead(data, philo) > 0)
			return ;
		if (data->must_eat)
			if (is_philo_full(data, philo) > 0)
				return ;
		usleep(500);
	}
}

static size_t	is_philo_dead(t_data *data, t_philo *philo)
{
	size_t	id;
	long	elapsed;
	long	current;

	id = 0;
	while (id < data->ph_count)
	{
		elapsed = ph_time_to_ms() - philo[id].last_meal;
		if (elapsed >= (long)data->die_ms)
		{
			current = ph_time_to_ms() - data->start_ms;
			data->dead = true;
			pthread_mutex_lock(&data->data_lock);
			printf("%ld %zu died\n", current, philo[id].index);
			pthread_mutex_unlock(&data->data_lock);
			return (2);
		}
		id++;
	}
	return (0);
}

static size_t	is_philo_full(t_data *data, t_philo *philo)
{
	size_t	i;

	i = 0;
	data->sated = 0;
	while (i < data->ph_count)
	{
		if (philo[i].meals_eaten >= data->must_eat)
			data->sated++;
		i++;
	}
	if (data->sated >= data->ph_count)
	{
		data->dead = true;
		return (2);
	}
	return (0);
}
