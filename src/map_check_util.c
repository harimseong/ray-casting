#include "cub3d.h"

int	is_map(const char *read_line)
{
	while (*read_line == ' ')
		++read_line;
	if (ft_isdigit(*read_line))
		return (1);
	return (0);
}

int	is_map_line(const char *read_line)
{
	if (read_line == NULL)
		return (1);
	while (*read_line && *read_line != '\n')
	{
		if (!ft_strchr("013NSWE ", *read_line++))
			return (0);
	}
	return (1);
}

