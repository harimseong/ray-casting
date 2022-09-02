#include "init_data.h"
#include "cub3d.h"
#include <stdint.h>

static void	init_mlx(t_mlx_data *mlx_data);
static void	init_player(t_map map, t_player *player);
static void	postprocess_map(t_map *map);

int	init_data(int argc, char **argv, t_mlx_data *mlx_data)
{
	ft_memset(mlx_data, 0, sizeof(*mlx_data));
	if (argc != 2)
		error_handler(ARGUMENT_ERROR);
	get_config_info(check_config_path(argv[1]), mlx_data);
	init_map(argv[1], mlx_data);
	init_mlx(mlx_data);
	init_player(mlx_data->map, &mlx_data->player);
	postprocess_map(&mlx_data->map);
	init_sprite_texture(mlx_data);
	init_sprite(mlx_data);
	collect_ptr_2d_garbage((void **)mlx_data->map.map);
	return (0);
}

static void	init_mlx(t_mlx_data *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE,
		RESIZABLE);
	if (mlx_data->mlx_ptr == NULL)
		error_handler(MLX_INIT_ERROR);
	mlx_data->main_img
		= mlx_new_image(mlx_data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_data->minimap
		= mlx_new_image(mlx_data->mlx_ptr, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (mlx_data->main_img == NULL || mlx_data->minimap == NULL)
		error_handler(MLX_IMG_ERROR);
	mlx_set_cursor_mode(mlx_data->mlx_ptr, MLX_MOUSE_DISABLED);
}

static void	init_player(t_map map, t_player *player)
{
	const uint32_t	direction = map.map[player->grid.y][player->grid.x];

	player->angle = M_PI_2 * (direction == 'E')
		+ M_PI * (direction == 'S')
		+ 3 * M_PI_2 * (direction == 'W');
	player->x = GRID_LEN * player->grid.x + GRID_LEN / 2.0;
	player->y = GRID_LEN * player->grid.y + GRID_LEN / 2.0;
	map.map[player->grid.y][player->grid.x] = '0';
}

static void	postprocess_map(t_map *map)
{
	int			idx;
	int			jdx;
	uint32_t	val;

	idx = 0;
	while (idx < map->height)
	{
		jdx = 0;
		while (jdx < map->width)
		{
			val = map->map[idx][jdx];
			if (val == ' ' || val == '0')
				map->map[idx][jdx] = MAP_EMPTY;
			else if (val == '1')
				map->map[idx][jdx] = MAP_WALL;
			else if (val == '2')
				map->map[idx][jdx] = MAP_DOOR_OPENED
					| (GRID_LEN << INFO_BITSHIFT);
			else if (val == '3')
				map->map[idx][jdx] = MAP_DOOR_CLOSED;
			else if (val > '3' && val < '9')
				map->map[idx][jdx] = MAP_SPRITE_NONBLOCK + ((val - '3') << INFO_BITSHIFT);
			++jdx;
		}
		++idx;
	}
}
