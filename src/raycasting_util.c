#include "MLX42.h"
#include "cub3d.h"
#include "raycasting.h"
#include <stdio.h>

static uint32_t	to_le(uint32_t color, double fog);
static uint32_t	apply_fog(uint32_t color, double fog);
static int get_pos(mlx_texture_t* texture, t_ray *point);

static const int32_t	g_half_screen_height = SCREEN_HEIGHT / 2;
static const int32_t	g_canvas_dist = 4 * PLAYER_SIZE;

uint32_t	get_color(t_mlx_data *data, t_ray *point, int32_t y)
{
	int				pos;
	mlx_texture_t	*wall_texture;
	uint32_t		color;
	int32_t			range;
	double 			fog;

	fog = fabs((double)y - g_half_screen_height) / g_half_screen_height;
	wall_texture = data->texture_list.wall[point->direction];
	pos = get_pos(wall_texture, point);
	/** pos = (lround(point->x) % GRID_LEN) + (lround(point->y) % GRID_LEN); */
	/** pos = wall_texture->width * pos / GRID_LEN; */
	range = g_canvas_dist * g_half_screen_height / point->distance;
	if (-range + g_half_screen_height > y)
		return (apply_fog(data->texture_list.floor_color, fog));
	else if (range + g_half_screen_height <= y)
		return (apply_fog(data->texture_list.ceiling_color, fog));
	y = (y - g_half_screen_height + range) * wall_texture->height / (2 * range);
	color = *((uint32_t *)wall_texture->pixels + \
			((int)y * wall_texture->width + pos));
	color = to_le(color, FOG_FACTOR / (point->distance + FOG_FACTOR));
	return (color);
}

static uint32_t	to_le(uint32_t color, double fog)
{
	unsigned char	bytes[4];
	uint32_t		ret;

	bytes[0] = (unsigned char)((color >> 24) & 0xff);
	bytes[1] = (unsigned char)((color >> 16) & 0xff);
	bytes[2] = (unsigned char)((color >> 8) & 0xff);
	bytes[3] = (unsigned char)((color >> 0) & 0xff);
	bytes[1] *= fog;
	bytes[2] *= fog;
	bytes[3] *= fog;
	ret = ((uint32_t)bytes[0] << 0) | \
		((uint32_t)bytes[1] << 8) | \
		((uint32_t)bytes[2] << 16) | \
		((uint32_t)bytes[3] << 24);
	return (ret);
}

static uint32_t	apply_fog(uint32_t color, double fog)
{
	unsigned char	bytes[4];
	uint32_t		ret;

	bytes[0] = (unsigned char)((color >> 24) & 0xff);
	bytes[1] = (unsigned char)((color >> 16) & 0xff);
	bytes[2] = (unsigned char)((color >> 8) & 0xff);
	bytes[3] = (unsigned char)((color >> 0) & 0xff);
	bytes[0] *= fog;
	bytes[1] *= fog;
	bytes[2] *= fog;
	ret = ((uint32_t)bytes[0] << 24) | \
		((uint32_t)bytes[1] << 16) | \
		((uint32_t)bytes[2] << 8) | \
		((uint32_t)bytes[3] << 0);
	return (ret);
}

static int get_pos(mlx_texture_t* texture, t_ray *point)
{
	int pos;

	pos = (lround(point->x) % GRID_LEN) + (lround(point->y) % GRID_LEN);
	if (point->direction == DOOR)
	{
		if ((lround(point->x) % HALF_GRID_LEN) == 0)
			pos = lround(point->y) % GRID_LEN;
		else if ((lround(point->y) % HALF_GRID_LEN) == 0)
			pos = lround(point->x) % GRID_LEN;
	}
	pos = texture->width * pos / GRID_LEN;
	return (pos);
}

int map_type_check(t_ray *ray, t_map *map, t_camera *camera)
{
	char type;

	type = map->map[lround(ray->y) / GRID_LEN][lround(ray->x) / GRID_LEN];
	if (type == '0' || type == '2')
		return (1);
	else if (type == '3')
	{
		if (ray->direction == NORTH)
		{
			ray->y -= GRID_LEN / 2.0;
			ray->x += -GRID_LEN / 2.0 * -1 * tan(camera->angle);
		}
		else if (ray->direction == SOUTH)
		{
			ray->y += GRID_LEN / 2.0;
			ray->x += -GRID_LEN / 2.0 * tan(camera->angle);
		}
		else if (ray->direction == EAST)
		{
			ray->x -= GRID_LEN / 2.0;
			ray->y += -GRID_LEN / 2.0 * -1 / tan(camera->angle);
		}
		else if (ray->direction == WEST)
		{
			ray->x += GRID_LEN / 2.0;
			ray->y += -GRID_LEN / 2.0 / tan(camera->angle);
		}
		ray->direction = DOOR;
	}
	return (0);
}
