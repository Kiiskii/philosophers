#include "philos.h"

void	ph_exit(char *msg)
{
	ph_putstr_fd(msg, 2);
	exit(1);
}
