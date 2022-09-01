#include "gun.h"

void gun_image_to_window(t_mlx_data *mlx_data, int gun_idx)
{
	uint32_t xy[2];
	uint32_t wh[2];

	xy[0] = 0;
	xy[1] = 0;
	wh[0] = mlx_data->texture_list.gun[gun_idx]->width;
	wh[1] = mlx_data->texture_list.gun[gun_idx]->height;
	if (mlx_data->gun_img)
		mlx_delete_image(mlx_data->mlx_ptr, mlx_data->gun_img);
	mlx_data->gun_img = mlx_texture_area_to_image(mlx_data->mlx_ptr, mlx_data->texture_list.gun[gun_idx], xy, wh);
	mlx_image_to_window(mlx_data->mlx_ptr, mlx_data->gun_img, SCREEN_WIDTH / 2 - wh[0] / 2, SCREEN_HEIGHT - wh[1] - 50 - gun_idx * 10);
}
