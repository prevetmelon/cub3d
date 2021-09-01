#include "cub3d.h"

void	bmp_header(t_win img, int fd)
{
	int	size_file;
	int	img_offset;

	img_offset = 54;
	size_file = img_offset + img.width * img.height * 4;
	write(fd, "BM", 2);
	write(fd, &size_file, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &img_offset, 4);
}

void	bmp_info(t_win img, int fd)
{
	int	size_header;
	int	size_img;
	int	plane;

	size_header = 40;
	size_img = img.width * img.height * 4;
	plane = 1;
	write(fd, &size_header, 4);
	write(fd, &img.width, 4);
	write(fd, &img.height, 4);
	write(fd, &plane, 2);
	write(fd, &img.bits_per_pixel, 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &size_img, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

void	bmp_img(t_win img, int fd)
{
	int	x;
	int	y;

	y = img.height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < img.width)
		{
			write(fd, &img.addr[y * img.line_length + x
				* img.bits_per_pixel / 8], 1);
			write(fd, &img.addr[y * img.line_length + x
				* img.bits_per_pixel / 8 + 1], 1);
			write(fd, &img.addr[y * img.line_length + x
				* img.bits_per_pixel / 8 + 2], 1);
			write(fd, "\0", 1);
			x++;
		}
		y--;
	}
}

int	screenshoot(t_all *all)
{
	int	fd;

	fd = open("screenshot.bmp", O_CREAT | O_WRONLY,
			S_IRWXU | S_IRWXG | S_IROTH);
	if (fd < 0)
		print_error(all, "Screen failed");
	all->win->height = all->res_y;
	all->win->width = all->res_x;
	bmp_header(*all->win, fd);
	bmp_info(*all->win, fd);
	bmp_img(*all->win, fd);
	close(fd);
	return (1);
}
