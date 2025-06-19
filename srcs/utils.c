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
	if (c == '\t' || c == '\n' || c == ' ')//lkjdsflsdjf
		return (1);
	return (0);
}

long	ph_time_to_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	solo_philo(t_philo *philo)
{
	t_data	*data;
	long	current_time;

	data = philo->data;
	pthread_mutex_lock(philo->r_fork);
	current_time = ph_time_to_ms() - data->start_ms;
	pthread_mutex_lock(&data->print_lock);
	printf("%ld %zu %s\n", current_time, philo->index, FORKING);
	pthread_mutex_unlock(&data->print_lock);
	while (!data->dead)
		usleep(500);
	pthread_mutex_unlock(philo->r_fork);
}
