#include "cub3d.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*s11 == '\0' && *s22 == '\0')
			break ;
		if (*s11 != *s22)
			return (*s11 - *s22);
		s11++;
		s22++;
		n--;
	}
	if (*s11 == '\0' && *s22 != '\0')
		return (1);
	return (0);
}

static	int	ft_check_remain(char *kek, char **remain)
{
	if (kek || *remain)
		return (1);
	else
	{
		free(*remain);
		*remain = NULL;
		return (0);
	}
}

void	free_kek(char **tmp, char **remain)
{
	free(*tmp);
	free(*remain);
}

static void	*read_remain(char **line, char **remain)
{
	char		*ptr_remain;
	char		*tmp;

	ptr_remain = NULL;
	*line = ft_strdup("");
	if (*remain != NULL)
	{
		ptr_remain = ft_strchr(*remain, '\n');
		if (ptr_remain != NULL)
		{
			*ptr_remain = '\0';
			tmp = *line;
			*line = ft_strjoin(*line, *remain);
			free(tmp);
			tmp = *remain;
			*remain = ft_strdup(++ptr_remain);
			free(tmp);
			return (ptr_remain);
		}
		tmp = *line;
		*line = ft_strdup(*remain);
		free_kek(&tmp, remain);
		*remain = NULL;
	}
	return (NULL);
}

int	get_next_line(int fd, char **line)
{
	int			read_val;
	static char	*remain;
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;
	char		*kek;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || read(fd, buf, 0) == -1)
		return (-1);
	kek = NULL;
	kek = read_remain(line, &remain);
	if (!kek)
		read_val = read(fd, buf, BUFFER_SIZE);
	while (!kek && read_val > 0)
	{
		buf[read_val] = '\0';
		kek = ft_strchr(buf, '\n');
		if (kek != NULL)
			full_kek(&kek, &remain);
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
		if (!kek)
			read_val = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_check_remain(kek, &remain));
}
