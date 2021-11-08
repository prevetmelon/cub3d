#include "cub3d.h"

int	quit(int keycode, int null)
{
	if (keycode == 1)
		printf("Exit game\n");
	exit(null);
}

void	napravo(t_all *all)
{
	if (all->map[(int)(all->plr->pos_y + cosf(all->plr->dir)
			* MOVE_SPEED)][(int)(all->plr->pos_x)] != '1')
		all->plr->pos_y += cosf(all->plr->dir) * MOVE_SPEED;
	if (all->map[(int)(all->plr->pos_y)][(int)(all->plr->pos_x
		- sinf(all->plr->dir) * MOVE_SPEED)] != '1')
		all->plr->pos_x -= sinf(all->plr->dir) * MOVE_SPEED;
}

void	nalevo(t_all *all)
{
	if (all->map[(int)(all->plr->pos_y - cosf(all->plr->dir)
			* MOVE_SPEED)][(int)(all->plr->pos_x)] != '1')
		all->plr->pos_y -= cosf(all->plr->dir) * MOVE_SPEED;
	if (all->map[(int)(all->plr->pos_y)][(int)(all->plr->pos_x
		+ sinf(all->plr->dir) * MOVE_SPEED)] != '1')
		all->plr->pos_x += sinf(all->plr->dir) * MOVE_SPEED;
}

void	nazad(t_all *all)
{
	if (all->map[(int)(all->plr->pos_y - sinf(all->plr->dir)
			* MOVE_SPEED)][(int)(all->plr->pos_x)] != '1')
		all->plr->pos_y -= sinf(all->plr->dir) * MOVE_SPEED;
	if (all->map[(int)(all->plr->pos_y)][(int)(all->plr->pos_x
		- cosf(all->plr->dir) * MOVE_SPEED)] != '1')
		all->plr->pos_x -= cosf(all->plr->dir) * MOVE_SPEED;
}

int	key_hook(int keycode, t_all *all)
{
	if (keycode == 123)
		all->plr->dir -= 0.1;
	if (keycode == 124)
		all->plr->dir += 0.1;
	if (keycode == 2)
		napravo(all);
	if (keycode == 0)
		nalevo(all);
	if (keycode == 1)
		nazad(all);
	if (keycode == 13)
	{
		if (all->map[(int)(all->plr->pos_y + sinf(all->plr->dir)
				* MOVE_SPEED)][(int)(all->plr->pos_x)] != '1')
			all->plr->pos_y += sinf(all->plr->dir) * MOVE_SPEED;
		if (all->map[(int)(all->plr->pos_y)][(int)(all->plr->pos_x
			+ cosf(all->plr->dir) * MOVE_SPEED)] != '1')
			all->plr->pos_x += cosf(all->plr->dir) * MOVE_SPEED;
	}
	if (keycode == 53)
		exit(0);
	rendering(all);
	return (0);
}
