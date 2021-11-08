#include "cub3d.h"

void	kek_lol(t_all *all, int sprite_size, int h_offset, int v_offset)
{
	int		i;
	int		j;

	i = -1;
	while (++i < sprite_size)
	{
		if (!(h_offset + i < -all->res_x / 2 || h_offset + i >= all->res_x / 2))
		{
			if (all->sprite.distance < all->hits[all->res_x / 2 + h_offset + i])
			{
				j = -1;
				while (++j < sprite_size)
				{
					if (!(v_offset + j < 0 || v_offset + j >= all->res_y))
					{
						my_mlx_pixel_put(all, all->res_x / 2 + h_offset
							+ i, v_offset + j, all->textures[4]
						[(j * SCALE / sprite_size)
							*SCALE + (i *SCALE / sprite_size)]);
					}
				}
			}
		}
	}
}

void	draw_sprite(t_sprite sprite, t_all *all)
{
	float	sprite_dir;
	int		h_offset;
	int		v_offset;
	int		sprite_size;

	sprite_dir = atan2(sprite.y - all->plr->pos_y * SCALE,
			sprite.x - all->plr->pos_x * SCALE);
	vector_normilize(&sprite_dir);
	vector_normilize(&all->plr->dir);
	while (sprite_dir - all->plr->dir > M_PI)
		sprite_dir -= 2 * M_PI;
	while (sprite_dir - all->plr->dir < -M_PI)
		sprite_dir += 2 * M_PI;
	sprite_size = SCALE * all->res_y / sprite.distance;
	h_offset = (((sprite_dir - all->plr->dir) * M_PI / 2) * all->res_x
			- sprite_size) / 2;
	v_offset = all->res_y / 2 - sprite_size / 2;
	all->sprite = sprite;
	kek_lol(all, sprite_size, h_offset, v_offset);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
}

void	sort_sprites(t_all *all)
{
	int			i;
	int			j;
	t_sprite	kek;

	i = 0;
	j = 0;
	while (i + 1 < all->s_count)
	{
		while (j + 1 < all->s_count - i)
		{
			if (all->sprites[j + 1].distance > all->sprites[j].distance)
			{
				kek = all->sprites[j];
				all->sprites[j] = all->sprites[j + 1];
				all->sprites[j + 1] = kek;
			}
			j++;
		}
		i++;
	}
}
