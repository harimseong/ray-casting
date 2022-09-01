#include "hook.h"
#include "cub3d.h"

static int	get_player_move_input(t_mlx_data *data, t_player *player);

void	key_event(t_mlx_data *data)
{
	static uint32_t	*door_ptr;

	if (!get_player_move_input(data, &data->player)
		&& mlx_is_key_down(data->mlx_ptr, MLX_KEY_F) && door_ptr == NULL)
		door_ptr = door_event(data);
	if (door_ptr != NULL)
	{
		if ((*door_ptr >> INFO_BITSHIFT) % 512 != 0)
			*door_ptr += DOOR_DIFF << INFO_BITSHIFT;
		else
		{
			*door_ptr ^= (*door_ptr >> INFO_BITSHIFT) == 512;
			door_ptr = NULL;
		}
	}
}

void	cursor_event(t_mlx_data *data)
{
	int32_t			x;
	int32_t			y;
	static int32_t	old_x;
	static int		start;

	if (start == 0)
	{
		mlx_get_mouse_pos(data->mlx_ptr, &old_x, &y);
		start = 1;
		return ;
	}
	mlx_get_mouse_pos(data->mlx_ptr, &x, &y);
	data->player.angle += (x - old_x) * MOUSE_SENSITIVITY;
	old_x = x;
	if (data->player.angle >= 2.0 * M_PI)
		data->player.angle -= 2.0 * M_PI;
	else if (data->player.angle < 0.0)
		data->player.angle += 2.0 * M_PI;
}

static int	get_player_move_input(t_mlx_data *data, t_player *player)
{
	double	move_x;
	double	move_y;
	double	side_x;
	double	side_y;
	int		has_moved;

	has_moved = 0;
	move_x = SPEED * sin(player->angle);
	move_y = SPEED * -cos(player->angle);
	side_x = (SPEED / 2.0) * -cos(player->angle);
	side_y = (SPEED / 2.0) * -sin(player->angle);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		exit(1);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		has_moved = player_move(player, move_x, move_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		has_moved = player_move(player, -move_x, -move_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
		has_moved = player_move(player, side_x, side_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
		has_moved = player_move(player, -side_x, -side_y, data);
	return (has_moved);
}
