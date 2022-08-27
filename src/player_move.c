#include "player_move.h"

static int is_y_grid(char **map, int player_xy[2]);
static int is_x_grid(char **map, int player_xy[2]);
inline static int	pos_to_grid(double pos, int cub_size, int size);

void player_move(t_player *player, double move_x, double move_y, t_mlx_data *data)
{
	int player_top_left[2];
	int re_pos;

	player_top_left[0] = player->x;
	player_top_left[1] = player->y;
	player_top_left[1] += move_y;
	re_pos = is_y_grid(data->map.map, player_top_left);
	if (re_pos)
		player_top_left[1] = re_pos;
	player_top_left[0] += move_x;
	re_pos = is_x_grid(data->map.map, player_top_left);
	if (re_pos)
		player_top_left[0] = re_pos;
	player->x = player_top_left[0];
	player->y = player_top_left[1];
	player->grid.x = player_top_left[0] / GRID_LEN;
	player->grid.y = player_top_left[1] / GRID_LEN;
}

static int is_y_grid(char **map, int player_xy[2])
{
	int grid_x1;
	int grid_y1;
	int grid_x2;
	int grid_y2;

	grid_x1 = pos_to_grid(player_xy[0], GRID_LEN, -(128 / 2));
	grid_y1 = pos_to_grid(player_xy[1], GRID_LEN, -(128 / 2));
	grid_x2 = pos_to_grid(player_xy[0], GRID_LEN, (128 / 2) - 1);
	grid_y2 = pos_to_grid(player_xy[1], GRID_LEN, (128 / 2) - 1);
	if (map[grid_y1][grid_x1] & 1 || map[grid_y1][grid_x2] & 1)
		return ((player_xy[1] / GRID_LEN) * GRID_LEN + 64);
	else if (map[grid_y2][grid_x1] & 1 || map[grid_y2][grid_x2] & 1)
		return ((player_xy[1] / GRID_LEN) * GRID_LEN + GRID_LEN - 64);
	return (0);
}

static int is_x_grid(char **map, int player_xy[2])
{
	int grid_x1;
	int grid_y1;
	int grid_x2;
	int grid_y2;

	grid_x1 = pos_to_grid(player_xy[0], GRID_LEN, -(128 / 2));
	grid_y1 = pos_to_grid(player_xy[1], GRID_LEN, -(128 / 2));
	grid_x2 = pos_to_grid(player_xy[0], GRID_LEN, (128 / 2) - 1);
	grid_y2 = pos_to_grid(player_xy[1], GRID_LEN, (128 / 2) - 1);
	if (map[grid_y1][grid_x1] & 1 || map[grid_y2][grid_x1] & 1)
		return ((player_xy[0] / GRID_LEN) * GRID_LEN + 64);
	else if (map[grid_y1][grid_x2] & 1 || map[grid_y2][grid_x2] & 1)
		return ((player_xy[0] / GRID_LEN) * GRID_LEN + GRID_LEN - 64);
	return (0);
}

inline static int	pos_to_grid(double pos, int cub_size, int size)
{
	return ((pos + size) / cub_size);
}
