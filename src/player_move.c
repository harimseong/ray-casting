#include "player_move.h"

static double is_y_grid(char **map, t_player *player);
static double is_x_grid(char **map, t_player *player);
inline static int	pos_to_grid(double pos, int cub_size, int size);

void player_move(t_player *player, double move_x, double move_y, t_mlx_data *data)
{
	double player_top_left[2];
	double re_pos;

	player_top_left[0] = player->x - PLAYER_SIZE / 2.0;
	player_top_left[1] = player->y - PLAYER_SIZE / 2.0;
	player_top_left[1] += move_y;
	re_pos = is_y_grid(data->map.map, player);
	if (re_pos)
		player_top_left[1] = re_pos;
	player_top_left[0] += move_x;
	re_pos = is_x_grid(data->map.map, player);
	if (re_pos)
		player_top_left[0] = re_pos;
	player->x = player_top_left[0] + PLAYER_SIZE / 2.0;
	player->y = player_top_left[1] + PLAYER_SIZE / 2.0;
}

static double is_y_grid(char **map, t_player *player)
{
	int grid_x1;
	int grid_y1;
	int grid_x2;
	int grid_y2;

	grid_x1 = pos_to_grid(player->x, GRID_LEN, 0);
	grid_y1 = pos_to_grid(player->y, GRID_LEN, 0);
	grid_x2 = pos_to_grid(player->x, GRID_LEN, PLAYER_SIZE - 1);
	grid_y2 = pos_to_grid(player->y, GRID_LEN, PLAYER_SIZE - 1);
	if (map[grid_y1][grid_x1] & 1 || map[grid_y1][grid_x2] & 1)
		return ((player->y / GRID_LEN) * GRID_LEN + GRID_LEN);
	else if (map[grid_y2][grid_x1] & 1 || map[grid_y2][grid_x2] & 1)
		return ((player->y / GRID_LEN) * GRID_LEN + GRID_LEN - PLAYER_SIZE);
	return (0);
}

static double is_x_grid(char **map, t_player *player)
{
	int grid_x1;
	int grid_y1;
	int grid_x2;
	int grid_y2;

	grid_x1 = pos_to_grid(player->x, GRID_LEN, 0);
	grid_y1 = pos_to_grid(player->y, GRID_LEN, 0);
	grid_x2 = pos_to_grid(player->x, GRID_LEN, PLAYER_SIZE - 1);
	grid_y2 = pos_to_grid(player->y, GRID_LEN, PLAYER_SIZE - 1);
	if (map[grid_y1][grid_x1] & 1 || map[grid_y2][grid_x1] & 1)
		return ((player->x / GRID_LEN) * GRID_LEN + GRID_LEN);
	else if (map[grid_y1][grid_x2] & 1 || map[grid_y2][grid_x2] & 1)
		return ((player->x / GRID_LEN) * GRID_LEN + GRID_LEN - PLAYER_SIZE);
	return (0);
}

inline static int	pos_to_grid(double pos, int cub_size, int size)
{
	return (((pos - PLAYER_SIZE / 2.0) + size) / cub_size);
}
