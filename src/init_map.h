#ifndef INIT_MAP_H
# define INIT_MAP_H

# include <fcntl.h>

# include "cub3d.h"
# include "error.h"
# include "get_next_line.h"
# include "garbage_collector/garbage_collector.h"

void	init_map(const char *path, t_mlx_data *mlx_data);
int		get_map_line(const char *path);
int		jump_to_map(const char *path, int map_line_num);
int		check_map_validity(char **map, int rows, int cols, t_ivec2 *player_pos);

#endif
