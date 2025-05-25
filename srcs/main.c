#include "philos.h"

int	main(int ac, char *av[])
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	ph_parse_input(ac, &av[1], &data);
	return (0);
}
