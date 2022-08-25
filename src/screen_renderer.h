#ifndef SCREEN_RENDERER_H
# define SCREEN_RENDERER_H

# include <stdio.h>
# include <math.h>

# include "cub3d.h"
# include "hook.h"
# include "minimap.h"
# include "raycasting.h"
# include "drawline.h"

//#include "sprite.h"

# define FOV (M_PI / 3)
# define MINIMAP_RAY_NUM (1)

void	screen_renderer(void *data);

#endif
