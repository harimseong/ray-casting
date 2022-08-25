#include "raycasting.h"

#include <stdio.h>

static uint32_t	to_le(uint32_t color);

uint32_t	get_color(t_mlx_data data, t_ray point, uint32_t y)
{
	int				pos;
	mlx_texture_t	*wall_texture;
	uint32_t		color;

	// TODO: lround may not be work
	pos = (lround(point.x) % GRID_LEN + (lround(point.y)) % GRID_LEN);
	wall_texture = data.texture_list.wall[point.direction];
	pos = wall_texture->width * pos / GRID_LEN;
	if (y >= wall_texture->height)
		y = 0;
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
