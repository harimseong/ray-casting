#include "minimap.h"
#include "cub3d.h"

static t_ivec2	transfer_pos(const t_player player, int x, int y, const t_map map);

// transfer pixel position to map position to grid position
static uint32_t	get_color(const t_ivec2 pos, const t_map map);

const static int	g_map_per_pixel = MINIMAP_GRID_NUM * GRID_LEN / MINIMAP_WIDTH;

void	render_minimap(t_mlx_data *data)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			color = get_color(transfer_pos(data->player, x, y), data->map);
			mlx_put_pixel(data->minimap, x, y, color);
			++x;
		}
		++y;
	}
}

static t_ivec2	transfer_pos(const t_player player, int x, int y, const t_map map)
{
	double	map_pos_x;
	double	map_pos_y;

	map_pos_x = (player.x - 3 * GRID_LEN) + g_map_per_pixel * x;
	map_pos_y = (player.y - 3 * GRID_LEN) + g_map_per_pixel * y;
	if ((map_pos_x < 0 || map_pos_x >= map.width * GRID_LEN)
		|| (map_pos_y < 0 || map_pos_y >= map.height * GRID_LEN))
		return ((t_ivec2){-1, -1});
	return ((t_ivec2){map_pos_x / GRID_LEN, map_pos_y / GRID_LEN});
}

static uint32_t	get_color(const t_ivec2 pos, const t_map map)
{
	
}
