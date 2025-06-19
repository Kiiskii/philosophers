#include "philos.h"

//static size_t	is_philo_full(t_data *data, t_philo *philo);
static size_t	is_philo_dead(t_data *data, t_philo *philo);

void	ph_monitor(t_data *data, t_philo *philo)
{
	while (data->start_ms > ph_time_to_ms())
		usleep(750);
	while (1)
	{
		if (data->must_eat)
			//if (is_philo_full(data, philo) > 0)
			if (data->sated == data->ph_count)
				return ;
		if (is_philo_dead(data, philo) > 0)
			return ;
		//usleep(500);
	}
}

static size_t	is_philo_dead(t_data *data, t_philo *philo)
{
	size_t	id;
	long	elapsed;

	id = 0;
	while (id < data->ph_count)
	{
		elapsed = ph_time_to_ms() - philo[id].last_meal;
		if (elapsed >= (long)data->die_ms)
		{
			pthread_mutex_lock(&data->print_lock);
			data->dead = true;
			printf("%ld %zu died\n", ph_time_to_ms() - data->start_ms, philo[id].index);
			//printf("%ld %zu %zu\n", philo[id].last_meal - data->start_ms, philo[id].index, philo[id].meals_eaten);
			pthread_mutex_unlock(&data->print_lock);
			return (2);
		}
		id++;
	}
	return (0);
}
/*
static size_t	is_philo_full(t_data *data, t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < data->ph_count)
	{
		if (philo[i].meals_eaten >= data->must_eat)
			data->sated++;
		i++;
	}
	if (data->sated == data->ph_count)
	{
		write(1, "HELLO\n", 6);
		return (2);
	}
	return (0);
}
*/
