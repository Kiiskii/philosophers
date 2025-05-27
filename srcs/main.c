#include "philos.h"

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
	ph_join_threads(&data, philo);
	return (0);
}
