#ifndef CUB3D_H
# define CUB3D_H
# define SCALE 128
# define MOVE_SPEED 0.25
# define RES_X_MAX 2560
# define RES_Y_MAX 1440
# define RES_X_MIN 200
# define RES_Y_MIN 200
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_p_flags
{
	int				r;
	int				n;
	int				s;
	int				e;
	int				w;
	int				sp;
	int				c;
	int				f;
}					t_p_flags;

typedef struct s_win
{
	void			*img;
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_win;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_player
{
	float			pos_x;
	float			pos_y;
	float			dir;
	float			start;
	float			end;
}					t_player;

typedef struct s_sprite
{
	float			x;
	float			y;
	float			distance;
}					t_sprite;

typedef struct s_bmp
{
	int				size;
	char			*img;
	unsigned char	header[14];
	unsigned char	info[40];
	unsigned char	pad[3];
	int				color;
	int				fd;
}					t_bmp;

typedef struct s_all
{
	t_win			*win;
	t_player		*plr;
	t_sprite		*sprites;
	int				res_x;
	int				res_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				clr_ceil;
	int				clr_floor;
	char			**map;
	int				count;
	int				s_count;
	int				**textures;
	float			*hits;
	float			start;
	float			end;
	char			*path;
	t_sprite		sprite;
	t_p_flags		fl;

}					t_all;

void	clear_image(t_all *all);
char	**make_map(t_all *all, char *path, int start);
void	my_mlx_pixel_put(t_all *all, int x, int y, int color);
size_t	slen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_next_line(int fd, char **line);
char	*ft_strdup(const char *s1);
char	*ft_strchr(char *s, int c);
void	rendering(t_all *all);
void	sort_sprites(t_all *all);
void	ft_cast_ray(t_all *a);
void	draw_sprite(t_sprite sprite, t_all *all);
void	vector_normilize(float *dir);
void	wall_is_stas(t_all *all, int x, int tex_x, int id);
int		screenshoot(t_all *all);
void	print_error(t_all *all, char *message);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		key_hook(int keycode, t_all *all);
int		quit(int keycode, int null);
void	load_textures(t_all *all);
int		ft_atoi(const char *str);
void	parser(t_all *all, char *path);
void	full_kek(char **kek, char **remain);
void	check_map(t_all *all);
int		ladya(t_all *all, int x, int y);
int		check(char c);
int		is_digit(char *s);
int		intlen(int number);
int		oh_my_map(char *line);
int		get_arg_count(char **arg);
void	set_path(t_all *all, char **path, char **arg, int *flag);
int		create_rgb(char *r, char *g, char *b, t_all *all);
int		ladya_nazad(t_all *all, int x, int y);
void	set_color(t_all *all, int *clr, char **arg, int *flah);
char	check_array(t_all *all, int x, int y);

#endif
