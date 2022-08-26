#include "screen_renderer.h"

void		render_main_img(t_mlx_data data);
static void	draw_minimap_ray(t_mlx_data *data, t_player p0, t_ray p1);
static void	crosshair_line(t_mlx_data *data, int pos, int len);
void		print_frame(void);

static const int 	g_ray_cnt = SCREEN_WIDTH / 2;
static const double	g_transfer_ratio = (double)MINIMAP_GRID_LEN / GRID_LEN;

void	screen_renderer(void *data)
{
	t_mlx_data	*mlx_data;

	mlx_data = (t_mlx_data *)data;
	(void)mlx_data;
//	render_sprite(mlx_data);
	key_event(mlx_data);
	cursor_event(mlx_data);
	render_minimap(*mlx_data);
	render_main_img(*mlx_data);
	print_frame();
}

void	print_frame(void)
{
	struct timeval	time1;
	static uint64_t		old_ms;
	uint64_t		ms;

		gettimeofday(&time1, NULL);
	ms = time1.tv_sec * 1000 + time1.tv_usec / 1000;
	printf("fps: %f\n", 1000.0 / (ms - old_ms));
	old_ms = ms;
}

void render_main_img(t_mlx_data data)
{
	int			idx;
	t_ray		point;
	t_player	camera;
	double		angle_diff;

	idx = 0;
	camera = data.player;
	camera.angle -= FOV * 0.5;
	camera.grid.x = lround(camera.x) / GRID_LEN;
	camera.grid.y = lround(camera.y) / GRID_LEN;
	angle_diff = FOV / g_ray_cnt;
	while (idx < g_ray_cnt)
	{
		point = detect_wall(camera, data.map);
		/** if (idx == g_ray_cnt / 2) */
		/**     print_detect_wall(camera, data.map); */
		point.distance *= cos(camera.angle - data.player.angle);
		/** printf("x : %f y : %f dis : %f direction : %d\n", point.x, point.y, point.distance, point.direction); */
		draw_col_line(&data, point, idx);
		if (idx % 6 == 0)
			draw_minimap_ray(&data, camera, point);
		camera.angle += angle_diff;
		++idx;
	}
	crosshair_line(&data, 6, 6);
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

void	crosshair_line(t_mlx_data *data, int pos, int len)
{
	int	idx;
	mlx_image_t	*img;

	idx = 0;
	img = data->main_img;
	while (idx < len)
	{
		mlx_put_pixel(img, (img->width >> 1) + pos + idx, img->height >> 1, 0x3fbf1fff);
		mlx_put_pixel(img, (img->width >> 1) + pos + idx + 1, (img->height >> 1) + 1, 0x000000ff);
		mlx_put_pixel(img, (img->width >> 1) - pos - idx, img->height >> 1, 0x3fbf1fff);
		mlx_put_pixel(img, (img->width >> 1) - pos - idx + 1, (img->height >> 1) + 1, 0x000000ff);
		mlx_put_pixel(img, img->width >> 1, (img->height >> 1) + pos + idx, 0x3fbf1fff);
		mlx_put_pixel(img, (img->width >> 1) + 1, (img->height >> 1) + pos + idx + 1, 0x000000ff);
		mlx_put_pixel(img, img->width >> 1, (img->height >> 1) - pos - idx, 0x3fbf1fff);
		mlx_put_pixel(img, (img->width >> 1) + 1, (img->height >> 1) - pos - idx + 1, 0x000000ff);
		++idx;
	}
}
