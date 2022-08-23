#include "cub3d.h"
#include "init_data.h"
#include "hook.h"
#include "screen_renderer.h"

int main(int argc, char **argv)
{
	t_mlx_data	mlx_data;

	init_data(argc, argv, &mlx_data);
	mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.main_img, 0, 0);
	mlx_put_string(mlx_data.mlx_ptr, "press [m] to open minimap", 0, 0);
	mlx_image_to_window(mlx_data.mlx_ptr, mlx_data.minimap, 0, 0);
	mlx_key_hook(mlx_data.mlx_ptr, key_hook, &mlx_data);
	/** mlx_cursor_hook(mlx_data.mlx_ptr, cursor_hook, &mlx_data); */
	mlx_loop_hook(mlx_data.mlx_ptr, screen_renderer, &mlx_data);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
