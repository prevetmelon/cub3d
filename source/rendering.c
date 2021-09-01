#include "cub3d.h"

void	wall_is_stas(t_all *all, int x, int tex_x, int id)
{
	int		vertical_line;
	int		y;
	float	tex_y;

	vertical_line = SCALE * all->res_y / (all->hits[x]);
	if (tex_x < 0)
		tex_y = 1;
	else
		tex_y = 0;
	y = all->res_y / 2 - vertical_line / 2;
	while (y <= all->res_y / 2 + vertical_line / 2)
	{
		my_mlx_pixel_put(all, x, y++,
			all->textures[id][(int) tex_y * SCALE + tex_x]);
		if (tex_y < 127)
			tex_y += 1.0 * (SCALE - 1) / vertical_line;
		if (tex_x < 0 && tex_y > SCALE)
			tex_y = SCALE;
		if (tex_x > 0 && tex_y > SCALE - 1)
			tex_y = SCALE - 1;
	}
}

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	if (y < all->res_y && x < all->res_x && y >= 0 && x >= 0
		&& color != 0xff0000)
	{
		*(unsigned int *)(all->win->addr
				+ (y * (all->win->line_length) + x
					* (all->win->bits_per_pixel / 8))) = color;
	}
}

void	clear_image(t_all *all)
{
	int	i;
	int	j;

	j = 0;
	while (j < all->res_y / 2)
	{
		i = 0;
		while (i < all->res_x)
		{
			my_mlx_pixel_put(all, i, j, all->clr_ceil);
			i++;
		}
		j++;
	}
	while (j >= all->res_y / 2 && j < all->res_y)
	{
		i = 0;
		while (i < all->res_x)
		{
			my_mlx_pixel_put(all, i, j, all->clr_floor);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

void	rendering(t_all *all)
{
	int	n;

	n = 0;
	clear_image(all);
	ft_cast_ray(all);
	while (n < all->s_count)
	{
		all->sprites[n].distance = hypotf(
				all->sprites[n].x - all->plr->pos_x * SCALE,
				all->sprites[n].y - all->plr->pos_y * SCALE);
		n++;
	}
	n = 0;
	sort_sprites(all);
	while (n < all->s_count)
	{
		draw_sprite(all->sprites[n], all);
		n++;
	}
}
