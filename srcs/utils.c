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

long	ph_time_to_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
