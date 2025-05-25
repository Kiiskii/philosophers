#include "philos.h"

//static int	string_to_number(char *str);
//static int	init_data(int ac, char **av, t_data *data);
static int	is_number(int ac, char **av);

void	ph_parse_input(int ac, char **av, t_data *data)
{
	int	err;

	(void)data;
	err = 0;
	if (ac != 5 && ac != 6)
		ph_exit(USAGE);
	if (is_number(ac, av) == 1)
		ph_exit(INVALID_NUMBER);
}

static int	is_number(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac) //FIX ME
	{
		j = 0;
		while (av[i][j])
		{
			if (j == 0 && av[i][j] == '+')
				continue ;
			else if (!(av[i][j] >= '0' || av[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
/*
static int	init_data(int ac, char **av, t_data *data)
{
	data.ph_count = string_to_number(av[1]);
	data.die_ms = string_to_number(av[2]);
	data.eat_ms = string_to_number(av[3]);
	data.sleep_ms = string_to_number(av[4]);
	if (ac == 6)
		data.must_eat = string_to_number(av[5]);
}

static int	string_to_number(char *str)
{
	int		i;
	size_t	num;

	i = 0;
	num = 0;
	if (str[0] == '-')
		return (-1);
	while (ft_isblank(str[i]) == 1)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		if (num > INT_MAX)
			return (-2);
		i++;
	}
	return ((int)num);
}
*/
