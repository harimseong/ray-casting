#include "hook.h"
#include <stdio.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_mlx_data	*data;
	double		move_x;
	double		move_y;


	data = param;
	move_x = SPEED * sin(data->player.angle * M_PI / 180);
	move_y = SPEED * -cos(data->player.angle * M_PI / 180);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(1);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		player_move(&data->player, move_x, move_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		player_move(&data->player, -move_x, -move_y, data);
	/** if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A)) */
		/** data->player.x -= 100; */
	/** if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D)) */
		/** data->player.x += 100; */
	/** if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_M)) */
	/**     data->screen.toggle_minimap = !data->screen.toggle_minimap; */
	/** if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_F) && data->player.near_door) */
	/**     act_door(&data->map, data->pnt); */
}
