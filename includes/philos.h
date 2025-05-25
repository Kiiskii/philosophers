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

typedef struct s_data
{
	int	ph_count;
	int	die_ms;
	int	eat_ms;
	int	sleep_ms;
	int	must_eat;
}		t_data;

void	ph_parse_input(int ac, char **av, t_data *data);
void	ph_exit(char *msg);

//utils
int	ph_putstr_fd(char *s, int fd);
int	ft_isblank(int c);

#endif
