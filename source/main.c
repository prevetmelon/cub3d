#include "../includes/cub3d.h"

void	print_error(t_all *all, char *message)
{
	printf("Error\n%s\n", message);
	free(all->plr);
	exit(0);
}

void	check_cubfile(t_all *all, char *cub_file)
{
	int	s;

	s = (int) slen(cub_file);
	if (cub_file[s - 1] != 'b' || cub_file[s - 2] != 'u'
		|| cub_file[s - 3] != 'c' || cub_file[s - 4] != '.')
		print_error(all, "Wrong cub file format");
}

void	check_shooting(t_all *all, char **argv)
{
	if (ft_strncmp(argv[2], "--save", slen(argv[2])) == 0)
	{
		screenshoot(all);
		exit(0);
	}
	else
		print_error(all, "Wrong third argument");
}

void	init_win(t_all *all, t_win *win)
{
	win->win = mlx_new_window(win->mlx, all->res_x, all->res_y, "Cub3D");
	win->img = mlx_new_image(win->mlx, all->res_x, all->res_y);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel,
			 &win->line_length, &win->endian);
}

int	main(int argc, char **argv)
{
	t_all	all;
	t_win	win;

	if (argc >= 2 && argc <= 3)
	{
		all.plr = malloc(sizeof(t_player));
		win.mlx = mlx_init();
		check_cubfile(&all, argv[1]);
		parser(&all, argv[1]);
		init_win(&all, &win);
		all.win = &win;
		all.textures = malloc(5 * sizeof(int *));
		load_textures(&all);
		all.hits = malloc(all.res_x * sizeof(float));
		rendering(&all);
		if (argc == 3)
			check_shooting(&all, argv);
		mlx_hook(win.win, 02, (1L << 0), key_hook, &all);
		mlx_hook(win.win, 17, (1L << 17), quit, 0);
		mlx_put_image_to_window(win.mlx, win.win, win.img, 0, 0);
		mlx_loop(win.mlx);
	}
	else
		printf("Error\nWrong number of arguments\n");
}
