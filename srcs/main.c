#include "philos.h"

//TODO: 


size_t	is_philo_dead(t_data *data, t_philo *philo)
{
	size_t	id;
	long	elapsed;

	id = 0;
	while (data->start_ms > ph_time_to_ms())
		usleep(500);
	while (id < data->ph_count)
	{
		elapsed = ph_time_to_ms() - philo[id].last_meal;
		if (elapsed >= (long)data->die_ms)
		{
			//pthread_mutex_lock(&data->print_lock);
			data->dead = true;
			printf("%ld %zu died\n", ph_time_to_ms() - data->start_ms, philo[id].index);
			//pthread_mutex_unlock(&data->print_lock);
			ph_final_cleanup(philo, data->ph_count);
			return (1);
		}
		id++;
	}
	return (0);
}

size_t	is_philo_full(t_data *data, t_philo *philo)
{
	size_t	id;

	id = 1;
	while (id <= data->ph_count)
	{
		//printf("\n%zu\n", philo[id].meals_eaten);
		if (philo[id].meals_eaten == data->must_eat)
		{
			data->sated++;
			if (data->sated == data->ph_count)
			{
				//printf("\n\n\n%zu\n\n\n", data->sated);
				ph_final_cleanup(philo, data->ph_count);
				return (1);
			}
		}
		id++;
	}
	return (0);
}

void	ph_monitor(t_data *data, t_philo *philo)
{

	while (1)
	{
		if (is_philo_dead(data, philo) > 0)
			return ;
		if (is_philo_full(data, philo) > 0)
			return ;
		usleep(500);
	}
}

int	main(int ac, char *av[])
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	memset(&data, 0, sizeof(t_data));
	ph_parse_input(ac - 1, &av[1], &data);
	ph_init_mutexes(&data);
	ph_init_philos(&data, &philo);
	ph_create_threads(&data, philo);
	ph_monitor(&data, philo);
	ph_join_threads(&data, philo);
	//ph_cleanup("Done\n", philo, data.ph_count);
	return (0);
}
