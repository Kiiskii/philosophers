#include "philos.h"

void	ph_init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_lock, NULL))
		ph_exit(INIT_PRINT_LOCK);
	if (pthread_mutex_init(&data->index_lock, NULL))
		ph_exit(INIT_INDEX_LOCK);
	data->current_index = 1;
}
