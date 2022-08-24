#include "screen_renderer.h"
#include "cub3d.h"

#include <stdio.h>


# define FOV (M_PI / 3)

void render_main_img(t_mlx_data data);

static const int g_ray_cnt = SCREEN_WIDTH / 2;

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

	idx = -1;
	camera = data.player;
	camera.angle -= FOV / 2;
	while (idx++ < g_ray_cnt)
	{
		point = detect_wall(camera, data.map);
		point.distance *= cos(camera.angle - data.player.angle);
		/** printf("x : %f y : %f dis : %f direction : %d\n", point.x, point.y, point.distance, point.direction); */
		draw_col_line(data, point, idx);
		camera.angle += FOV / g_ray_cnt;
	}
}
