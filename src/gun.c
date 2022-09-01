#include "gun.h"
#include "MLX42.h"
#include "cub3d.h"

void gun_image_to_window(t_mlx_data *mlx_data, int gun_idx)
{
	uint32_t xy[2];
	uint32_t wh[2];
	mlx_texture_t *gun_texture;

	gun_texture = mlx_data->texture_list.gun[gun_idx];
	xy[0] = 0;
	xy[1] = 0;
	wh[0] = gun_texture->width;
	wh[1] = gun_texture->height;
	if (mlx_data->gun_img)
		mlx_delete_image(mlx_data->mlx_ptr, mlx_data->gun_img);
	mlx_data->gun_img = mlx_texture_area_to_image(mlx_data->mlx_ptr, gun_texture, xy, wh);
	mlx_image_to_window(mlx_data->mlx_ptr, mlx_data->gun_img,
			SCREEN_WIDTH / 2 - wh[0] / 2,
			SCREEN_HEIGHT - wh[1] - 50 - gun_idx * 10);
}

void ammo_string_to_window(t_mlx_data *mlx_data, char *ammo_num)
{

	if (mlx_data->ammo_img)
		mlx_delete_image(mlx_data->mlx_ptr, mlx_data->ammo_img);
	mlx_data->ammo_img = mlx_put_string(mlx_data->mlx_ptr, ammo_num, SCREEN_WIDTH / 2 + 10, SCREEN_HEIGHT / 2);
}

