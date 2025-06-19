#include "philos.h"

static size_t	string_to_number(char *str);
static int		init_data(int ac, char **av, t_data *data);
static int		is_number(int ac, char **av);

void	ph_parse_input(int ac, char **av, t_data *data)
{
	int	err;

	err = 0;
	if (ac != 4 && ac != 5)
	{
		ph_exit(data, USAGE);
		return ;
	}
	if (is_number(ac, av) == 1)
	{
		ph_exit(data, INVALID_NUMBER);
		return ;
	}
	err = init_data(ac, av, data);
	if (data->ph_count > PHILO_MAX)
		ph_exit(data, PH_COUNT);
	else if (err < 0)
		ph_exit(data, OVER_INTMAX);
}

static int	is_number(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (j == 0 && av[i][j] == '+')
			{
				j++;
				continue ;
			}
			else if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	init_data(int ac, char **av, t_data *data)
{
	data->ph_count = string_to_number(av[0]);
	if (data->ph_count > INT_MAX || data->ph_count == 0)
		return (-1);
	data->die_ms = string_to_number(av[1]);
	if (data->die_ms > INT_MAX || data->die_ms == 0)
		return (-1);
	data->eat_ms = string_to_number(av[2]);
	if (data->eat_ms > INT_MAX || data->eat_ms == 0)
		return (-1);
	data->sleep_ms = string_to_number(av[3]);
	if (data->sleep_ms > INT_MAX || data->sleep_ms == 0)
		return (-1);
	if (ac == 5)
	{
		data->must_eat = string_to_number(av[4]);
		if (data->must_eat > INT_MAX || data->must_eat == 0)
			return (-1);
	}
	data->start_ms = ph_time_to_ms() + 200;
	return (0);
}

static size_t	string_to_number(char *str)
{
	int		i;
	size_t	num;

	i = 0;
	num = 0;
	while (str[i])
	{
		num = num * 10 + str[i] - '0';
		if (num > INT_MAX)
			return (num);
		i++;
	}
	return (num);
}
