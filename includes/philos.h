#ifndef PHILOS_H
# define PHILOS_H

# include "error_msgs.h"	//error_messages
# include <stdio.h>			//printf()
# include <pthread.h>		//pthread
# include <stdlib.h>		//malloc(), free()
# include <unistd.h>		//write(), usleep()
# include <limits.h>		//INT_MAX
# include <sys/time.h>		//gettimeofday()
# include <string.h>		//memset()
# include <stdbool.h>		//bool datatype

typedef struct s_data
{
	size_t			ph_count;
	size_t			die_ms;
	size_t			eat_ms;
	size_t			sleep_ms;
	size_t			must_eat;
	size_t			current_index;
	pthread_t		*threads;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	index_lock;
}		t_data;

typedef struct s_philo
{
	size_t	index;
	t_data	*data;
}		t_philo;

void	ph_parse_input(int ac, char **av, t_data *data);
void	ph_exit(char *msg);
void	ph_init_mutexes(t_data *data);
void	ph_init_philos(t_data *data, t_philo **philo);
void	ph_create_threads(t_data *data, t_philo *philo);
void	ph_join_threads(t_data *data, t_philo *philo);
void	run_routine(void *arg);

//utils
int	ph_putstr_fd(char *s, int fd);
int	ft_isblank(int c);

#endif
