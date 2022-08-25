#ifndef HOOK_H
# define HOOK_H

# include <math.h>

# include "cub3d.h"
# include "player_move.h"

# define SPEED (50)
/** # define ANGULAR_SPEED (0.157) // ~= M_PI / 20 */
# define ANGULAR_SPEED (0.06)

void	key_event(t_mlx_data *data);
void	cursor_hook(double xpos, double ypos, void* param);

void	move_forward(t_mlx_data *mlx_data);
void	move_left(t_mlx_data *mlx_data);
void	move_backward(t_mlx_data *mlx_data);
void	move_right(t_mlx_data *mlx_data);

#endif
