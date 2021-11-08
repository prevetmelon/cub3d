#include "cub3d.h"

void	load_image(t_all *all, char *path, int **texture, t_win *win)
{
	win->img = mlx_xpm_file_to_image(all->win->mlx, path, &win->width,
			&win->height);
	if (win->img == NULL)
		print_error(all, "Picture not found");
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
			&win->line_length, &win->endian);
	*texture = (int *) win->addr;
}

void	load_textures(t_all *all)
{
	t_win	win;

	load_image(all, all->no, &all->textures[0], &win);
	load_image(all, all->we, &all->textures[1], &win);
	load_image(all, all->ea, &all->textures[2], &win);
	load_image(all, all->so, &all->textures[3], &win);
	load_image(all, all->s, &all->textures[4], &win);
}
