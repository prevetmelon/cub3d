#include "cub3d.h"

int	is_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}

int	intlen(int number)
{
	int	i;

	i = 0;
	while (number / 10)
	{
		number /= 10;
		i++;
	}
	return (i);
}

int	oh_my_map(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!(line[i] == '1' || line[i] == ' '))
			return (-1);
	}
	return (1);
}

int	get_arg_count(char **arg)
{
	int	f;

	f = 0;
	while (arg[f])
		f++;
	return (f);
}

void	set_path(t_all *all, char **path, char **arg, int *flag)
{
	int	s;

	*flag = 1;
	s = (int)slen(arg[1]);
	if (get_arg_count(arg) != 2)
		print_error(all, "Wrong number of arguments");
	if (arg[1][s - 1] == 'm' && arg[1][s - 2] == 'p' && arg[1][s - 3] == 'x'
	   && arg[1][s - 4] == '.')
		*path = arg[1];
	else
		print_error(all, "Wrong file format");
}
