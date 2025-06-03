#include "philos.h"

void	ph_monitor(t_data *data, t_philo *philo)
{
	size_t	i;

	while (1)
	{
		i = 0;
		while (i < data->ph_count)
		{
			long elapsed = ph_time_to_ms() - philo[i].last_meal;
			if (elapsed > (long)data->die_ms)
			{
				pthread_mutex_lock(&data->print_lock);
				printf("%ld %zu died\n", ph_time_to_ms() - data->start_ms, philo[i].index);
				pthread_mutex_unlock(&data->print_lock);
				data->dead = true;
				return;
			}
			i++;
		}
		usleep(1000);
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
	return (0);
}
