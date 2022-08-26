#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>

# include "cub3d.h"
# include "player_move.h"

# define INF_GUARD (0.015)

# define EAST (0)
# define WEST (1)
# define SOUTH (2)
# define NORTH (3)

typedef t_player t_camera;

t_ray		detect_wall(t_camera ray, t_map map);
void		draw_col_line(t_mlx_data data, t_ray point, int idx);
uint32_t	get_color(t_mlx_data data, t_ray point, int32_t y);

t_ray print_detect_wall(t_camera camera, t_map map);

#endif
