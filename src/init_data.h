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
# define LIGHT_SPRITE_TEXTURE ("./images/light.png")
# define BARREL_SPRITE_TEXTURE ("./images/barrel.png")
# define PILLAR_SPRITE_TEXTURE ("./images/pillar.png")
# define GUN_SPRITE_TEXTURE_1 ("./images/gun1.png")
# define GUN_SPRITE_TEXTURE_2 ("./images/gun2.png")
# define GUN_SPRITE_TEXTURE_3 ("./images/gun3.png")

int		init_data(int argc, char **argv, t_mlx_data *mlx_data);
void	init_map(const char *path, t_mlx_data *mlx_data);
int		get_map_line(const char *path);
int		jump_to_map(const char *path, int map_line_num);
int		check_map_validity(uint32_t **map, int rows, int cols, t_ivec2 *player_pos);

#endif
