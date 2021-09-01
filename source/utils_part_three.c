#include "cub3d.h"

int	create_rgb(char *r, char *g, char *b, t_all *all)
{
	int		i_r;
	int		i_g;
	int		i_b;

	i_r = ft_atoi(r);
	i_g = ft_atoi(g);
	i_b = ft_atoi(b);
	if (i_r < 0 || i_r > 255 || i_g < 0 || i_g > 255 || i_b < 0 || i_b > 255
		|| intlen(i_r) > 3 || intlen(i_g) > 3 || intlen(i_b) > 3)
		print_error(all, "Not valid color");
	return (i_r << 16 | i_g << 8 | i_b);
}

void	set_color(t_all *all, int *clr, char **arg, int *flah)
{
	char	**stroka;

	*flah = 1;
	if (get_arg_count(arg) != 2)
		print_error(all, "Wrong number of arguments");
	stroka = ft_split(arg[1], ',');
	if (get_arg_count(stroka) == 3 && is_digit(stroka[0]) == 1
		&& is_digit(stroka[1]) == 1 && is_digit(stroka[2]) == 1)
		*clr = create_rgb(stroka[0], stroka[1], stroka[2], all);
	else
		print_error(all, "Not valid color");
}

int	check(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (-1);
}

char	check_array(t_all *all, int x, int y)
{
	int	len;

	if (y < 0 || y > all->count)
		print_error(all, "Not valid map 1 ");
	len = (int) slen(all->map[y]);
	if (x < 0 || x >= len)
		print_error(all, "Not valid map 2");
	return (all->map[y][x]);
}

int	ladya_nazad(t_all *all, int x, int y)
{
	int	j;

	j = -1;
	while (check_array(all, x, y - ++j) != '1')
	{
		if (y - j == 0 || check(all->map[y - j][x]) == -1)
			return (-1);
	}
	return (0);
}
