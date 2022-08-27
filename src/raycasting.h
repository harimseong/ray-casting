#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>

# include "cub3d.h"
# include "player_move.h"
# include "minimap.h"

# define INF_GUARD (0.015)
# define FOG_FACTOR (800)

# define HALF_GRID_LEN (256)

# define EAST (0)
# define WEST (1)
# define SOUTH (2)
# define NORTH (3)
# define DOOR (4)

typedef t_player t_camera;

t_ray		detect_wall(t_camera ray, t_map map);
uint32_t	get_color(t_mlx_data *data, t_ray *point, int32_t y);
int			map_type_check(t_ray *ray, t_map *map, t_camera *camera);

#endif
