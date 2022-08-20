#include "cub3d.h"
#include "libft.h"

int main(int argc, char **argv)
{
	t_mlx_data	mlx_data;

	init_data(argc, argv, &mlx_data);
	mlx_loop_hook(mlx_data.mlx_ptr);
	mlx_loop(mlx_data.mlx_ptr);
	return (0);
}
