#include "cub3d.h"

void	vector_normilize(float *dir)
{
	if (*dir < 0)
		*dir += M_PI * 2;
	if (*dir > M_PI * 2)
		*dir -= M_PI * 2;
}

void	kekomania(t_all *all, t_player ray, int x)
{
	int	r;
	int	h;

	r = (int)(ray.pos_x / SCALE * 200);
	h = (int)(ray.pos_y / SCALE * 200);
	if (r % 2 != 0)
		r--;
	if (h % 2 != 0)
		h--;
	if (r == (int)ray.pos_x / SCALE * 200
		&& all->map[(int)(ray.pos_y / SCALE)][(int)(ray.pos_x / SCALE -
												   1)] != '1')
		wall_is_stas(all, x - 1, (int)ray.pos_y % SCALE, 1);
	else if (r + 2 == ((int)(ray.pos_x) / SCALE + 1) * 200 &&
			 all->map[(int)(ray.pos_y / SCALE)][(int)(ray.pos_x / SCALE + 1)]
			 	 != '1')
		wall_is_stas(all, x - 1, -(int) ray.pos_y % SCALE, 2);
	else if (h == ((int)(ray.pos_y) / SCALE) * 200
		&& all->map[(int)(ray.pos_y / SCALE - 1)][(int)(ray.pos_x
		/ SCALE)] != '1')
		wall_is_stas(all, x - 1, -(int)ray.pos_x % SCALE, 0);
	else
		wall_is_stas(all, x - 1, (int)ray.pos_x % SCALE, 3);
}

void	ft_cast_ray(t_all *a)
{
	int			x;
	t_player	r;

	x = 0;
	r = *a->plr;
	r.pos_x = a->plr->pos_x * SCALE;
	r.pos_y = a->plr->pos_y * SCALE;
	a->start = r.dir - M_PI / 6;
	a->end = r.dir + M_PI / 6;
	while (x < a->res_x && a->start < a->end)
	{
		r.pos_x = a->plr->pos_x * SCALE;
		r.pos_y = a->plr->pos_y * SCALE;
		while (a->map[(int)(r.pos_y / SCALE)][(int)(r.pos_x / SCALE)] != '1')
		{
			r.pos_x += cos(a->start);
			r.pos_y += sin(a->start);
		}
		a->hits[x++] = hypotf(r.pos_x - a->plr->pos_x * SCALE, r.pos_y
				- a->plr->pos_y * SCALE) * cosf(a->start - a->plr->dir);
		kekomania(a, r, x);
		a->start += M_PI / 3 / a->res_x;
	}
	mlx_put_image_to_window(a->win->mlx, a->win->win, a->win->img, 0, 0);
}
