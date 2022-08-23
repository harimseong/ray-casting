#ifndef HOOK_H
# define HOOK_H

# include <math.h>

# include "cub3d.h"
# include "player_move.h"

# define SPEED (50)

void	key_hook(mlx_key_data_t keydata, void* param);
void	cursor_hook(double xpos, double ypos, void* param);

#endif
