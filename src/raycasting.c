#include "raycasting.h"
#include "cub3d.h"
#include <stdio.h>

t_ray detect_x_wall(t_camera camera, t_map map);
t_ray detect_y_wall(t_camera camera, t_map map);
inline static double	get_distance(t_ray ray, t_camera camera);
inline static int		boundary_check(t_ray ray, t_map map);

t_ray print_detect_x_wall(t_camera camera, t_map map);
t_ray print_detect_y_wall(t_camera camera, t_map map);

t_ray print_detect_wall(t_camera camera, t_map map)
{
	t_ray x_point;
	t_ray y_point;

	printf("===================\n");
	if (camera.angle < 0.0)
		camera.angle += 2.0 * M_PI;
	else if (camera.angle >= 2.0 * M_PI)
		camera.angle -= 2.0 * M_PI;
	/** if ((camera.angle <= M_PI_2 - INF_GUARD || camera.angle >= 3 * M_PI_2 + INF_GUARD) */
	/**         ||(camera.angle >= M_PI_2 + INF_GUARD && camera.angle <= 3 * M_PI_2 - INF_GUARD)) */
		y_point = print_detect_y_wall(camera, map);
	/** if ((camera.angle >= INF_GUARD && camera.angle <= M_PI - INF_GUARD) */
	/**     || (camera.angle >= M_PI + INF_GUARD && camera.angle <= M_PI * 2 - INF_GUARD)) */
		x_point = print_detect_x_wall(camera, map);
	printf("===================\n");
	if (x_point.distance < y_point.distance)
		return (x_point);
	return (y_point);
}

t_ray print_detect_x_wall(t_camera camera, t_map map)
{
	t_ray	ray;
	double	dy;
	int		direction_flag;

	direction_flag = 1;
	ray.x = (camera.grid.x + 1) * GRID_LEN;
	ray.direction = WEST;
	if (camera.angle >= M_PI)
	{
		direction_flag = -1;
		ray.x = camera.grid.x * GRID_LEN - 1;
		ray.direction = EAST;
	}
	ray.y = camera.y - (ray.x - camera.x) / tan(camera.angle);
	dy = -GRID_LEN * direction_flag / tan(camera.angle);
		/** printf("x wall : x : %d y : %d\n", ray.x, ray.y); */
	while (!boundary_check(ray, map)
		&& map.map[lround(ray.y) / GRID_LEN][lround(ray.x) / GRID_LEN] != '1')
	{
		ray.x += GRID_LEN * direction_flag;
		ray.y += dy;
		/** printf("x wall : x : %d y : %d\n", ray.x, ray.y); */
	}
	ray.distance = get_distance(ray, camera)
		+ boundary_check(ray, map) * INT32_MAX;
	ray.x += (direction_flag == -1);
	return (ray);
}

t_ray print_detect_y_wall(t_camera camera, t_map map)
{
	t_ray	ray;
	double	dx;
	int		direction_flag;

	direction_flag = 1;
	ray.y = (camera.grid.y + 1) * GRID_LEN;
	ray.direction = SOUTH;
	if (camera.angle <= M_PI_2 || camera.angle >= M_PI_2 * 3)
	{
		direction_flag = -1;
		ray.y = camera.grid.y * GRID_LEN - 1;
		ray.direction = NORTH;
	}
	ray.x = camera.x - (ray.y - camera.y) * tan(camera.angle);
	dx = -GRID_LEN * direction_flag * tan(camera.angle);
	while (!boundary_check(ray, map)
		&& map.map[lround(ray.y) / GRID_LEN][lround(ray.x) / GRID_LEN] != '1')
	{
		ray.y += GRID_LEN * direction_flag;
		ray.x += dx;
	}
	ray.distance = get_distance(ray, camera)
		+ boundary_check(ray, map) * INT32_MAX;
	ray.y += (direction_flag == -1);
	return (ray);
}


t_ray detect_wall(t_camera camera, t_map map)
{
	t_ray x_point;
	t_ray y_point;

	if (camera.angle < 0.0)
		camera.angle += 2.0 * M_PI;
	else if (camera.angle >= 2.0 * M_PI)
		camera.angle -= 2.0 * M_PI;
	/** if ((camera.angle <= M_PI_2 - INF_GUARD || camera.angle >= 3 * M_PI_2 + INF_GUARD) */
	/**         ||(camera.angle >= M_PI_2 + INF_GUARD && camera.angle <= 3 * M_PI_2 - INF_GUARD)) */
		y_point = detect_y_wall(camera, map);
	/** if ((camera.angle >= INF_GUARD && camera.angle <= M_PI - INF_GUARD) */
	/**     || (camera.angle >= M_PI + INF_GUARD && camera.angle <= M_PI * 2 - INF_GUARD)) */
		x_point = detect_x_wall(camera, map);
	if (x_point.distance <= y_point.distance)
		return (x_point);
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
		direction_flag = -1;
		ray.x = camera.grid.x * GRID_LEN - 1;
		ray.direction = EAST;
	}
	ray.y = camera.y - (ray.x + (direction_flag == -1) - camera.x) / tan(camera.angle);
		/** + (tan(camera.angle) >= 0 ? 1 : -1) */
		/** * direction_flag; */
	dy = -GRID_LEN * direction_flag / tan(camera.angle);
	while (!boundary_check(ray, map)
		&& map.map[lround(ray.y) / GRID_LEN][lround(ray.x) / GRID_LEN] != '1')
	{
		ray.x += GRID_LEN * direction_flag;
		ray.y += dy;
	}
	ray.distance = get_distance(ray, camera)
		+ boundary_check(ray, map) * INT32_MAX;
	ray.x += (direction_flag == -1);
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
		direction_flag = -1;
		ray.y = camera.grid.y * GRID_LEN - 1;
		ray.direction = NORTH;
	}
	ray.x = camera.x - (ray.y + (direction_flag == -1) - camera.y) * tan(camera.angle);
	dx = -GRID_LEN * direction_flag * tan(camera.angle);
	while (!boundary_check(ray, map)
		&& map.map[lround(ray.y) / GRID_LEN][lround(ray.x) / GRID_LEN] != '1')
	{
		ray.y += GRID_LEN * direction_flag;
		ray.x += dx;
	}
	ray.distance = get_distance(ray, camera)
		+ boundary_check(ray, map) * INT32_MAX;
	ray.y += (direction_flag == -1);
	return (ray);
}

inline static double	get_distance(t_ray ray, t_camera camera)
{
	return (sqrt(pow(ray.x - camera.x, 2.0) + pow(ray.y - camera.y, 2.0)));
}

inline static int	boundary_check(t_ray ray, t_map map)
{
	if (ray.x >= 0 && lround(ray.x) < GRID_LEN * map.width
		&& ray.y >= 0 && lround(ray.y) < GRID_LEN * map.height)
		return (0);
	return (1);
}
