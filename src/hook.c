#include "hook.h"

static int	gun_event(t_mlx_data *mlx_data);

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
	static int	is_gun_event;
	double	move_x;
	double	move_y;
	double	side_x;
	double	side_y;
	int		is_event_occur;

	is_event_occur = 0;
	move_x = SPEED * sin(player->angle);
	move_y = SPEED * -cos(player->angle);
	side_x = (SPEED / 2.0) * -cos(player->angle);
	side_y = (SPEED / 2.0) * -sin(player->angle);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		esc_exit(data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		is_event_occur = player_move(player, move_x, move_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		is_event_occur = player_move(player, -move_x, -move_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
		is_event_occur = player_move(player, side_x, side_y, data);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
		is_event_occur = player_move(player, -side_x, -side_y, data);
	if (is_gun_event || mlx_is_key_down(data->mlx_ptr, MLX_KEY_SPACE))
	{
		is_gun_event = gun_event(data);
		is_event_occur = 1;
	}
	return (is_event_occur);
}

static int	gun_event(t_mlx_data *mlx_data)
{
	static int idx;
	static int ammo = 10;

	if (ammo == 0)
		return (0);
	if (idx == 0)
		gun_image_to_window(mlx_data, 1);
	else if (idx == 2)
		gun_image_to_window(mlx_data, 2);
	else if (idx == 4)
	{
		ammo--;
		gun_image_to_window(mlx_data, 0);
		ammo_string_to_window(mlx_data, ft_itoa(ammo));
		idx = 0;
		return (0);
	}
	idx++;
	return (1);
}
