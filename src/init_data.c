#include "init_data.h"
#include <stdio.h>

void	init_mlx(t_mlx_data *mlx_data);

int	init_data(int argc, char **argv, t_mlx_data *mlx_data)
{
	ft_memset(mlx_data, 0, sizeof(*mlx_data));
	if (argc != 2)
		error_handler(ARGUMENT_ERROR);
	get_config_info(check_config_path(argv[1]), mlx_data);
	init_map(argv[1], mlx_data);
	init_mlx(mlx_data);
	return (0);
}

void	init_mlx(t_mlx_data *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE,
		RESIZABLE);
}

