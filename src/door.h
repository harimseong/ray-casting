#ifndef DOOR_H
# define DOOR_H

# include <math.h>
# include <stdio.h>

# include "cub3d.h"

# define DOOR_DISTANCE (GRID_LEN >> 1)
# define DOOR_DIFF (32)

uint32_t	*door_event(t_mlx_data *data);
int		check_east_door(t_ray *ray, uint32_t *type, double angle);
int		check_west_door(t_ray *ray, uint32_t *type, double angle);
int		check_south_door(t_ray *ray, uint32_t *type, double angle);
int		check_north_door(t_ray *ray, uint32_t *type, double angle);
t_ray	detect_door(t_player camera, t_map map);

#endif
