#include "cub3d.h"
#include "error.h"
#include "garbage_collector/garbage_collector.h"
#include "init_map.h"
#include "read_config.h"

static void get_map_size(int fd, t_mlx_data *mlx_data);
static void load_map(int fd, t_mlx_data *mlx_data);

void print_map_info(t_map *map)
{
	int idx;

	idx = 0;
	printf("map width : %d\n", map->width);
	printf("map hegiht : %d\n", map->height);
	while (map->map[idx])
		printf("%s\n", map->map[idx++]);
}

void init_map(const char *path, t_mlx_data *mlx_data)
{
	int map_line_num;

	map_line_num = get_map_line(path);
	get_map_size(jump_to_map(path, map_line_num), mlx_data);
	load_map(jump_to_map(path, map_line_num), mlx_data);
	print_map_info(&mlx_data->map);
	if (check_map_validity(mlx_data->map.map, mlx_data->map.height, mlx_data->map.width))
		error_handler(MAP_INVALID_ERROR);
}

void get_map_size(int fd, t_mlx_data *mlx_data)
{
	char	*read_line;
	int		max_map_width;

	max_map_width = 0;
	while (1)
	{
		read_line = remove_newline(get_next_line(fd));
		collect_ptr_garbage((void*)read_line);
		if (!read_line)
			break;
		if (!is_map_line(read_line))
			error_handler(MAP_INVALID_ERROR);
		mlx_data->map.height++;
		max_map_width = ft_strlen(read_line);
		if (max_map_width >= mlx_data->map.width)
			mlx_data->map.width = max_map_width;
		free(read_line);
	}
	mlx_data->map.map = (char**)malloc(sizeof(char*) *
			(mlx_data->map.height + 1));
	if (!mlx_data->map.map)
		error_handler(MALLOC_ERROR);
	close(fd);
	mlx_data->map.map[mlx_data->map.height] = NULL;
}

void load_map(int fd, t_mlx_data *mlx_data)
{
	char	*read_line;
	int		idx;
	char	*map_line;

	idx = 0;
	while (1)
	{
		read_line = remove_newline(get_next_line(fd));
		if (!read_line)
			break;
		map_line = (char*)malloc(sizeof(char) * mlx_data->map.width + 1);
		ft_memset(map_line, ' ', mlx_data->map.width);
		map_line[mlx_data->map.width] = '\0';
		ft_memcpy(map_line, read_line, ft_strlen(read_line));
		mlx_data->map.map[idx++] = map_line;
		free(read_line);
	}
	close(fd);
	collect_fd_garbage(0);
}
