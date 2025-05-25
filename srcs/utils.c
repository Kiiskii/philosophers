#include "philos.h"

int	ph_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (write(fd, s, 1) == -1)
			return (-1);
		i++;
		s++;
	}
	return (i);
}

int	ft_isblank(int c)
{
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}
