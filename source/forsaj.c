#include "cub3d.h"

void	full_kek(char **kek, char **remain)
{
	**kek = '\0';
	*kek += 1;
	*remain = ft_strdup(*kek);
}
