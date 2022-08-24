#include "raycasting.h"
#include <stdint.h>

t_ray detect_x_wall(t_camera camera, t_map map);
t_ray detect_y_wall(t_camera camera, t_map map);
static double get_distance(t_ray ray, t_camera camera);

t_ray detect_wall(t_camera camera, t_map map)
{
	t_ray x_point;
	t_ray y_point;

	x_point.distance = INT32_MAX;
	y_point.distance = INT32_MAX;
	if ((camera.angle <= M_PI_2 - INF_GUARD || camera.angle >= 3 * M_PI_2 + INF_GUARD)
			||(camera.angle >= M_PI_2 + INF_GUARD && camera.angle <= 3 * M_PI_2 - INF_GUARD))
		y_point = detect_y_wall(camera, map);
	/** if ((camera.angle >= INF_GUARD && camera.angle <= M_PI - INF_GUARD) */
	/**         || (camera.angle >= M_PI + INF_GUARD && camera.angle <= M_PI * 2 - INF_GUARD)) */
	/**     x_point = detect_x_wall(camera, map); */
	/** if (x_point.distance < y_point.distance) */
	/**     return (x_point); */
	return (y_point);
}

void draw_col_line(t_mlx_data data, t_ray point, int idx)
{
	// put pixel cnt
	uint32_t y;
	uint32_t color;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = get_color(data, point, y);
		mlx_put_pixel(data.main_img, 2 * idx, y, color);
		mlx_put_pixel(data.main_img, 2 * idx + 1, y, color);
		y++;
	}
}

t_ray detect_x_wall(t_camera camera, t_map map)
{
	t_ray	ray;
	double	dy;
	int		direction_flag;

	direction_flag = 1;
	ray.x = (camera.grid.x + 1) * GRID_LEN;
	ray.direction = WEST;
	if (camera.angle >= M_PI)
	{
		ray.direction = EAST;
		direction_flag = -1;
		ray.x = camera.grid.x * GRID_LEN - 1;
	}
	ray.y = camera.y - (ray.x - camera.x) / tan(camera.angle);
	dy = -(GRID_LEN * direction_flag / tan(camera.angle));
	// TODO: lround may not be work
	while (map.map[lround(ray.y) / GRID_LEN][lround(ray.x) / GRID_LEN] != '1')
	{
		ray.x += GRID_LEN * direction_flag;
		ray.y += dy;
	}
	ray.distance = get_distance(ray, camera);
	return (ray);
}

t_ray detect_y_wall(t_camera camera, t_map map)
{
	t_ray	ray;
	double	dx;
	int		direction_flag;

	direction_flag = 1;
	ray.y = (camera.grid.y + 1) * GRID_LEN;
	ray.direction = SOUTH;
	if (camera.angle <= M_PI_2 || camera.angle >= M_PI_2 * 3)
	{
		ray.direction = NORTH;
		direction_flag = -1;
		ray.y = camera.grid.y * GRID_LEN - 1;
	}
	ray.x = camera.x - (ray.y - camera.y) * tan(camera.angle);
	dx = -(GRID_LEN * direction_flag * tan(camera.angle));
	while (map.map[lround(ray.y) / GRID_LEN][lround(ray.x) / GRID_LEN] != '1')
	{
		ray.y += GRID_LEN * direction_flag;
		ray.x += dx;
	}
	ray.distance = get_distance(ray, camera);
	return (ray);
}

static double get_distance(t_ray ray, t_camera camera)
{
	return (sqrt(pow(ray.x - camera.x, 2) + pow(ray.y - camera.y, 2)));
}
