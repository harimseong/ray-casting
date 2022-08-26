#include "screen_renderer.h"

void		render_main_img(t_mlx_data data);
static void	draw_minimap_ray(t_mlx_data *data, t_player p0, t_ray p1);

static const int 	g_ray_cnt = SCREEN_WIDTH / 2;
static const double	g_scale = (double)MINIMAP_GRID_LEN / GRID_LEN;

void	screen_renderer(void *data)
{
	t_mlx_data	*mlx_data;
	/** static int	frame; */

	mlx_data = (t_mlx_data *)data;
	(void)mlx_data;
	/** printf("%d\n", frame++); */
//	render_sprite(mlx_data);
	key_event(mlx_data);
	render_minimap(*mlx_data);
	render_main_img(*mlx_data);
}

void render_main_img(t_mlx_data data)
{
	int			idx;
	t_ray		point;
	t_player	camera;

	idx = 0;
	camera = data.player;
	camera.angle -= FOV / 2;
	camera.grid.x = lround(camera.x) / GRID_LEN;
	camera.grid.y = lround(camera.y) / GRID_LEN;
	while (idx < g_ray_cnt)
	{
		point = detect_wall(camera, data.map);
		/** if (idx == g_ray_cnt / 2) */
		/**     print_detect_wall(camera, data.map); */
		point.distance *= cos(camera.angle - data.player.angle);
		/** printf("x : %f y : %f dis : %f direction : %d\n", point.x, point.y, point.distance, point.direction); */
		draw_col_line(data, point, idx);
		if (idx == g_ray_cnt / 2)
			draw_minimap_ray(&data, camera, point);
		camera.angle += (double)FOV / g_ray_cnt;
		++idx;
	}
}

static void	draw_minimap_ray(t_mlx_data *data, t_player p0, t_ray p1)
{
	t_vec2	origin;
	t_vec2	point;
	double	temp_x;
	double	angle;

	angle = data->player.angle;
	point = (t_vec2){p1.x - p0.x, p1.y - p0.y};
	point.x *= g_scale;
	point.y *= g_scale;
	origin = (t_vec2){MINIMAP_WIDTH >> 1, MINIMAP_HEIGHT >> 1};
	temp_x = point.x;
	point.x = temp_x * cos(angle) + point.y * sin(angle);
	point.y = -temp_x * sin(angle) + point.y * cos(angle);
	point.x += origin.x;
	point.y += origin.y;
	drawline(data->minimap, origin, point);
}
