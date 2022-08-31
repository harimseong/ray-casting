#include "screen_renderer.h"
#include "MLX42.h"
#include "cub3d.h"

static void	render_main_img(t_mlx_data *data);
static void	draw_minimap_ray(t_mlx_data *data, t_player p0, t_ray p1);

static const int 	g_ray_cnt = RAY_CNT;
static const double	g_transfer_ratio = (double)MINIMAP_GRID_LEN / GRID_LEN;

void	screen_renderer(void *data)
{
	t_mlx_data	*mlx_data;

	mlx_data = (t_mlx_data *)data;
	key_event(mlx_data);
	cursor_event(mlx_data);
	render_minimap(*mlx_data);
	render_main_img(mlx_data);
	user_interface(mlx_data);
}

static void render_main_img(t_mlx_data *data)
{
	int				idx;
	t_ray			point;
	t_player		camera;
	double			angle_diff;
	static double	depth_buffer[SCREEN_WIDTH];

	idx = 0;
	camera = data->player;
	camera.angle -= FOV * 0.5;
	angle_diff = FOV / g_ray_cnt;
	while (idx < g_ray_cnt)
	{
		point = detect_wall(camera, data->map);
		point.distance *= cos(camera.angle - data->player.angle);
		draw_col_line(data, point, idx);
		if (idx % 6 == 0)
			draw_minimap_ray(data, camera, point);
		camera.angle += angle_diff;
		depth_buffer[idx] = point.distance;
		++idx;
	}
	render_sprite(data, depth_buffer, g_ray_cnt);
}

void draw_col_line(t_mlx_data *data, t_ray point, int idx)
{
	// put pixel cnt
	uint32_t y;
	uint32_t color;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = get_color(data, &point, y);
		mlx_put_pixel(data->main_img, 2 * idx, y, color);
		mlx_put_pixel(data->main_img, 2 * idx + 1, y, color);
		y++;
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
	point.x *= g_transfer_ratio;
	point.y *= g_transfer_ratio;
	origin = (t_vec2){MINIMAP_WIDTH >> 1, MINIMAP_HEIGHT >> 1};
	temp_x = point.x;
	point.x = temp_x * cos(angle) + point.y * sin(angle);
	point.y = -temp_x * sin(angle) + point.y * cos(angle);
	point.y += origin.y;
	if (point.y < 0)
	{
		point.x *= origin.y / (origin.y - point.y);
		point.y = 0;
	}
	point.x += origin.x;
	drawline(data->minimap, origin, point);
}

