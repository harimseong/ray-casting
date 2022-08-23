#ifndef HOOK_H
# define HOOK_H

# include "cub3d.h"

void	key_hook(mlx_key_data_t keydata, void* param);
void	cursor_hook(double xpos, double ypos, void* param);

void	move_forward(t_mlx_data *mlx_data);
void	move_left(t_mlx_data *mlx_data);
void	move_backward(t_mlx_data *mlx_data);
void	move_right(t_mlx_data *mlx_data);

#endif
