#include "init_data.h"
#include "minimap.h"
#include "error.h"

static void	init_mlx(t_mlx_data *mlx_data);
static void	init_sprite(t_mlx_data *mlx_data);
static void	init_player(t_mlx_data *mlx_data);

int	init_data(int argc, char **argv, t_mlx_data *mlx_data)
{
	ft_memset(mlx_data, 0, sizeof(*mlx_data));
	if (argc != 2)
		error_handler(ARGUMENT_ERROR);
	get_config_info(check_config_path(argv[1]), mlx_data);
	init_map(argv[1], mlx_data);
	init_mlx(mlx_data);
	init_sprite(mlx_data);
	init_player(mlx_data);
	return (0);
}

static void	init_mlx(t_mlx_data *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE,
		RESIZABLE);
	if (mlx_data->mlx_ptr == NULL)
		error_handler(MLX_INIT_ERROR);
	mlx_data->main_img = mlx_new_image(mlx_data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_data->minimap = mlx_new_image(mlx_data->mlx_ptr, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (mlx_data->main_img == NULL || mlx_data->minimap == NULL)
		error_handler(MLX_IMG_ERROR);
	mlx_set_cursor_mode(mlx_data->mlx_ptr, MLX_MOUSE_HIDDEN);
}

static void	init_sprite(t_mlx_data *mlx_data)
{
	(void)mlx_data;
}

static void	init_player(t_mlx_data *mlx_data)
{
	t_player		*player = &mlx_data->player;
	const t_map		map = mlx_data->map;
	const char		direction = map.map[player->grid.y][player->grid.x];

	player->angle = 90.0 * (direction == 'E')
		+ 180.0 * (direction == 'S')
		+ 270.0 * (direction == 'W');
	player->x = GRID_LEN * player->grid.x + GRID_LEN / 2.0;
	player->y = GRID_LEN * player->grid.y + GRID_LEN / 2.0;
}
