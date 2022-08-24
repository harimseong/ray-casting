#include "raycasting.h"

#include <stdio.h>

uint32_t	get_color(t_mlx_data data, t_ray point, uint32_t y)
{
	int				pos;
	mlx_texture_t	*wall_texture;
	uint32_t		color;

	// TODO: lround may not be work
	pos = (lround(point.x) % GRID_LEN + (lround(point.y) + 1) % GRID_LEN);
	/** printf("x : %ld y : %ld\n",lround(point.x) % GRID_LEN, */
	/**         (lround(point.y) + 1) % GRID_LEN); */
	wall_texture = data.texture_list.wall[0];
	pos = wall_texture->width * pos / GRID_LEN;
	if (y >= wall_texture->height)
		y = 0;
	color = *((uint32_t *)wall_texture->pixels + \
			((int)y * wall_texture->width + pos));
	return (color);
}
