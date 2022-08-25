#include "minimap.h"
#include "raycasting.h"

#include <stdio.h>

static uint32_t	to_le(uint32_t color);

static const int32_t	g_half_screen_height = SCREEN_HEIGHT / 2;
static const int32_t	g_canvas_dist = 4 * PLAYER_SIZE;

uint32_t	get_color(t_mlx_data data, t_ray point, int32_t y)
{
	int				pos;
	mlx_texture_t	*wall_texture;
	uint32_t		color;
	int32_t			range;

	// TODO: lround may not be work
	wall_texture = data.texture_list.wall[point.direction];
	pos = (lround(point.x) % GRID_LEN) + (lround(point.y) % GRID_LEN);
	range = g_canvas_dist * g_half_screen_height / point.distance;
	if (-range + g_half_screen_height > y
		|| range + g_half_screen_height <= y)
		return (0x000000ff);
	y = (y - g_half_screen_height + range) * wall_texture->height / (2 * range);
	color = *((uint32_t *)wall_texture->pixels + \
			((int)y * wall_texture->width + pos));
	color = to_le(color);
	return (color);
}

static uint32_t	to_le(uint32_t color)
{
	unsigned char	bytes[4];
	uint32_t		ret;

	bytes[0] = (unsigned char)((color >> 24) & 0xff);
	bytes[1] = (unsigned char)((color >> 16) & 0xff);
	bytes[2] = (unsigned char)((color >> 8) & 0xff);
	bytes[3] = (unsigned char)((color >> 0) & 0xff);
	ret = ((uint32_t)bytes[0] << 0) | \
		((uint32_t)bytes[1] << 8) | \
		((uint32_t)bytes[2] << 16) | \
		((uint32_t)bytes[3] << 24);
	return (ret);
}
