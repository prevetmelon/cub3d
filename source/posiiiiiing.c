#include "cub3d.h"

int	ladya(t_all *all, int x, int y)
{
	int	j;

	if (ladya_nazad(all, x, y) == -1)
		return (-1);
	j = -1;
	while (check_array(all, x, y + ++j) != '1')
	{
		if (y + j == all->count || check(all->map[y + j][x]) == -1)
			return (-1);
	}
	j = -1;
	while (check_array(all, x - ++j, y) != '1')
	{
		if (x - j == 0 || check(all->map[y][x - j]) == -1)
			return (-1);
	}
	j = -1;
	while (check_array(all, x + ++j, y) != '1')
	{
		if (x + j == (int) slen(all->map[y]) - 1
			|| check(all->map[y][x + j]) == -1)
			return (-1);
	}
	return (0);
}

int	check_all_flahs(t_all *all)
{
	if (all->fl.r == 1 && all->fl.n == 1 && all->fl.s == 1 && all->fl.w == 1
		&& all->fl.e == 1 && all->fl.sp == 1 && all->fl.c == 1
		&& all->fl.f == 1)
		return (1);
	return (-1);
}

void	set_res(t_all *all, char **arg)
{
	all->fl.r = 1;
	if (get_arg_count(arg) != 3)
		print_error(all, "Wrong number of arguments");
	if (is_digit(arg[1]) == 1 && is_digit(arg[2]) == 1)
	{
		all->res_y = ft_atoi(arg[2]);
		all->res_x = ft_atoi(arg[1]);
	}
	else
		print_error(all, "Not correct resolution");
	if (all->res_x < RES_X_MIN)
		all->res_x = RES_X_MIN;
	if (all->res_y < RES_Y_MIN)
		all->res_y = RES_Y_MIN;
	if (all->res_x > RES_X_MAX || slen(arg[1]) > 7)
		all->res_x = RES_X_MAX;
	if (all->res_y > RES_Y_MAX || slen(arg[2]) > 7)
		all->res_y = RES_Y_MAX;
}

int	p_p(t_all *all, char **arg, char *line, int i)
{
	if (ft_strncmp(arg[0], "R", slen(arg[0])) == 0 && all->fl.r == 0)
		set_res(all, arg);
	else if (ft_strncmp(arg[0], "NO", slen(arg[0])) == 0 && all->fl.n == 0)
		set_path(all, &all->no, arg, &all->fl.n);
	else if (ft_strncmp(arg[0], "SO", slen(arg[0])) == 0 && all->fl.s == 0)
		set_path(all, &all->so, arg, &all->fl.s);
	else if (ft_strncmp(arg[0], "WE", slen(arg[0])) == 0 && all->fl.w == 0)
		set_path(all, &all->we, arg, &all->fl.w);
	else if (ft_strncmp(arg[0], "EA", slen(arg[0])) == 0 && all->fl.e == 0)
		set_path(all, &all->ea, arg, &all->fl.e);
	else if (ft_strncmp(arg[0], "S", slen(arg[0])) == 0 && all->fl.sp == 0)
		set_path(all, &all->s, arg, &all->fl.sp);
	else if (ft_strncmp(arg[0], "C", slen(arg[0])) == 0 && all->fl.c == 0)
		set_color(all, &all->clr_ceil, arg, &all->fl.c);
	else if (ft_strncmp(arg[0], "F", slen(arg[0])) == 0 && all->fl.f == 0)
		set_color(all, &all->clr_floor, arg, &all->fl.f);
	else if (oh_my_map(line) == 1 && check_all_flahs(all) == 1)
	{
		all->map = make_map(all, all->path, i);
		check_map(all);
		return (1);
	}
	else
		return (0);
	return (-1);
}

void	parser(t_all *all, char *path)
{
	int		fd;
	char	*line;
	char	**arg;
	int		i;
	int		k;

	i = 0;
	all->path = path;
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			i++;
			continue ;
		}
		arg = ft_split(line, ' ');
		k = p_p(all, arg, line, i);
		if (k == 1)
			break ;
		else if (k == 0)
			print_error(all, "Not valid map");
		i++;
	}
}
