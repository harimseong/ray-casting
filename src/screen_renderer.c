#include <stdio.h>

#include "screen_renderer.h"
#include "minimap.h"
//#include "sprite.h"
//#include "raycast.h"

void	screen_renderer(void *data)
{
	t_mlx_data	*mlx_data;
	static int	frame;

	mlx_data = (t_mlx_data *)data;
	(void)mlx_data;
	printf("%d\n", frame++);
//	render_main_img(mlx_data);
//	render_sprite(mlx_data);
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_ESCAPE))
		mlx_close_window(mlx_data->mlx_ptr);
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_UP))
		mlx_data->player.y -= 25;
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_DOWN))
		mlx_data->player.y += 25;
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_LEFT))
		mlx_data->player.x -= 25;
	if (mlx_is_key_down(mlx_data->mlx_ptr, MLX_KEY_RIGHT))
		mlx_data->player.x += 25;
	render_minimap(*mlx_data);
}
