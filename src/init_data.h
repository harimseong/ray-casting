#ifndef INIT_DATA_H
# define INIT_DATA_H

# include <stdio.h>
# include <math.h>

# include "cub3d.h"
# include "read_config.h"
# include "minimap.h"
# include "error.h"
# include "sprite.h"
# include "get_next_line.h"
# include "garbage_collector/garbage_collector.h"

# define RESIZABLE (0)
# define SPRITE_TEXTURE_PATH_1 ("./images/goodgreenlight.png")

int		init_data(int argc, char **argv, t_mlx_data *mlx_data);
void	init_map(const char *path, t_mlx_data *mlx_data);
int		get_map_line(const char *path);
int		jump_to_map(const char *path, int map_line_num);
int		check_map_validity(uint32_t **map, int rows, int cols,
		t_ivec2 *player_pos);

#endif
