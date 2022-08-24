#include "hook.h"
#include <stdio.h>

void	key_event(t_mlx_data *data)
{
	double		move_x;
	double		move_y;

	move_x = SPEED * sin(data->player.angle);
	move_y = SPEED * -cos(data->player.angle);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		exit(1);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		player_move(&data->player, move_x, move_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		player_move(&data->player, -move_x, -move_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
		data->player.angle -= ANGULAR_SPEED;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
		data->player.angle += ANGULAR_SPEED;
	if (data->player.angle >= 2.0 * M_PI)
		data->player.angle -= 2.0 * M_PI;
	else if (data->player.angle < 0.0)
		data->player.angle += 2.0 * M_PI;
	/** if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_M)) */
	/**     data->screen.toggle_minimap = !data->screen.toggle_minimap; */
	/** if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_F) && data->player.near_door) */
	/**     act_door(&data->map, data->pnt); */
}

void	cursor_hook(double xpos, double ypos, void* param)
{
	(void)xpos;
	(void)ypos;
	(void)param;
}
