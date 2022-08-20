#include "../includes/cub3d.h"

int	jump_to_map(t_mlx_data *data, char *map_path, int map_line_count)
{
	int		fd;
	char	*read_line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		error_msg("file open error", MAP_INIT_ERROR, data);
	while (map_line_count--)
	{
		read_line = get_next_line(fd);
		free(read_line);
	}
	return (fd);
}

int	find_map(t_mlx_data *data, char *map_path, int *map_line_count)
{
	int		fd;
	char	*read_line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		error_msg("file open error", MAP_INIT_ERROR, data);
	close(fd);
	gnl_flush(fd);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		error_msg("file open error", MAP_INIT_ERROR, data);
	while (1)
	{
		read_line = get_next_line(fd);
		if (map_check(read_line))
			break ;
		++*map_line_count;
		free(read_line);
	}
	if (!map_check(read_line))
		error_msg("invalid map", MAP_INIT_ERROR, data);
	free(read_line);
	return (fd);
}

int	check_map(t_mlx_data *data, t_map *map_data, int fd)
{
	char	*read_line;
	int		cub_x;

	map_data->cub_y = 1;
	while (1)
	{
		read_line = get_next_line(fd);
		if (!read_line || !map_line_check(read_line))
			break ;
		map_data->cub_y++;
		cub_x = ft_strlen(read_line) - 1;
		if (cub_x >= map_data->cub_x)
			map_data->cub_x = cub_x;
		free(read_line);
	}
	close(fd);
	if (!map_line_check(read_line))
		error_msg("invalid map", MAP_INIT_ERROR, data);
	map_data->map = (char **)malloc(sizeof(char *) * (map_data->cub_y + 1));
	if (!map_data->map)
		error_msg("malloc error", MAP_INIT_ERROR, data);
	map_data->map[map_data->cub_y] = NULL;
	return (0);
}

int	load_map(t_map *map_data, int fd)
{
	char	*read_line;
	char	*map_line;
	int		idx;

	idx = 0;
	while (1)
	{
		read_line = get_next_line(fd);
		if (!read_line)
			break ;
		map_line = malloc(map_data->cub_x + 1);
		ft_memset(map_line, ' ', map_data->cub_x);
		map_line[map_data->cub_x] = 0;
		ft_memcpy(map_line, read_line, ft_strlen(read_line) - 1);
		map_data->map[idx++] = map_line;
		free(read_line);
	}
	close(fd);
	return (0);
}

int	init_map(t_mlx_data *data)
{
	t_map	*map_data;
	char	*map_path;
	int		fd;
	int		map_line_count;

	map_data = &data->map;
	map_data->cub_size = GRID;
	map_path = map_data->map_path;
	map_data->map = NULL;
	map_line_count = 0;
	fd = find_map(data, map_path, &map_line_count);
	map_data->cub_x = 0;
	check_map(data, map_data, fd);
	fd = jump_to_map(data, map_path, map_line_count);
	load_map(map_data, fd);
	if (check_map_validity(map_data->map, map_data->cub_y, map_data->cub_x))
		error_msg("invalid map", MAP_INIT_ERROR, data);
	map_data->width = GRID * map_data->cub_x;
	map_data->height = GRID * map_data->cub_y;
	return (0);
}
