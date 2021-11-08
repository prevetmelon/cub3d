#include "cub3d.h"

void	set_plr_dir(t_all *all, char bookva)
{
	if (bookva == 'S')
		all->plr->dir = M_PI / 2;
	if (bookva == 'N')
		all->plr->dir = 3 * M_PI / 2;
	if (bookva == 'W')
		all->plr->dir = M_PI;
	if (bookva == 'E')
		all->plr->dir = 0;
}

void	check_map(t_all *all)
{
	int	x;
	int	y;

	y = 0;
	while (y <= all->count)
	{
		x = 0;
		while (all->map[y][x])
		{
			if (check(all->map[y][x]) == 1)
			{
				if (ladya(all, x, y) == -1)
					print_error(all, "Not valid map");
			}
			else if (all->map[y][x] != '1' && all->map[y][x] != ' ')
				print_error(all, "Not valid map");
			x++;
		}
		y++;
	}
}

void	cycle_one(t_all *all, int start, char **map, char *path)
{
	int		i;
	int		j;
	int		fd;
	char	*line;

	j = 0;
	i = 0;
	fd = open(path, O_RDONLY);
	while (i <= all->count)
	{
		get_next_line(fd, &line);
		if (i >= start)
		{
			map[i - start] = line;
			while (map[i - start][j] != '\0')
			{
				if (map[i - start][j] == '2')
					all->s_count++;
				j++;
			}
			j = 0;
		}
		i++;
	}
}

void	cycle_two(t_all *all, char **map, int start, int n)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= all->count - start)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' ||
				map[i][j] == 'E')
			{
				set_plr_dir(all, map[i][j]);
				all->plr->pos_y = i;
				all->plr->pos_x = j;
			}
			if (map[i][j] == '2')
			{
				all->sprites[n].x = ((float) j) * SCALE;
				all->sprites[n].y = ((float) i) * SCALE;
				n++;
			}
		}
	}
}

char	**make_map(t_all *all, char *path, int start)
{
	int		fd;
	char	**map;
	char	*line;
	int		n;

	n = 0;
	all->count = 0;
	all->s_count = 0;
	fd = open(path, O_RDONLY);
	while ((get_next_line(fd, &line) > 0))
	{
		all->count++;
		free(line);
	}
	map = malloc((sizeof(char *) * (all->count + 1 - start)));
	close(fd);
	cycle_one(all, start, map, path);
	all->sprites = malloc(all->s_count * sizeof(t_sprite));
	cycle_two(all, map, start, n);
	all->count -= start;
	return (map);
}
