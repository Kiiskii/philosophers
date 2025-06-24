#include "philos.h"

int	main(int ac, char *av[])
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	memset(&data, 0, sizeof(t_data));
	ph_parse_input(ac - 1, &av[1], &data);
	if (!data.exit)
		ph_init_mutexes(&data);
	if (!data.exit)
		ph_init_philos(&data, &philo);
	if (!data.exit)
		ph_create_threads(&data, philo);
	if (!data.exit)
		ph_monitor(&data, philo);
	if (!data.exit)
		ph_join_threads(&data, philo, data.ph_count);
	if (data.exit)
		return (1);
	ph_final_cleanup(philo);
	return (0);
}
