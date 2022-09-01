#include "exit.h"

void	esc_exit(t_mlx_data *mlx_data)
{
	mlx_close_window(mlx_data->mlx_ptr);
	mlx_terminate(mlx_data->mlx_ptr);
	dump_garbage();
	exit(0);
}
