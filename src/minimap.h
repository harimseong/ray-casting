#ifndef MINIMAP_H
# define MINIMAP_H

# include <math.h>

# include "cub3d.h"

# define MINIMAP_WIDTH (384)
# define MINIMAP_HEIGHT (384)
# define MINIMAP_GRID_LEN (32)
# define MINIMAP_GRID_NUM (12)

# define PLAYER_SIZE (16) // MINIMAP_GRID_LEN / 2
# define PLAYER_COLOR (0xff0f0fff)

void	render_minimap(t_mlx_data data);

#endif
