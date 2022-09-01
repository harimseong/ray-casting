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
# define ENEMY_SPRITE_TEXTURE_1 ("./images/enemy1.png")
# define ENEMY_SPRITE_TEXTURE_2 ("./images/enemy2.png")
# define ENEMY_SPRITE_TEXTURE_3 ("./images/enemy3.png")
# define ENEMY_SPRITE_TEXTURE_4 ("./images/enemy4.png")
# define ENEMY_SPRITE_TEXTURE_5 ("./images/enemy5.png")
# define ENEMY_SPRITE_TEXTURE_6 ("./images/enemy6.png")
# define ENEMY_SPRITE_TEXTURE_7 ("./images/enemy7.png")
# define ENEMY_SPRITE_TEXTURE_8 ("./images/enemy8.png")

int		init_data(int argc, char **argv, t_mlx_data *mlx_data);
void	init_map(const char *path, t_mlx_data *mlx_data);
int		get_map_line(const char *path);
int		jump_to_map(const char *path, int map_line_num);
int		check_map_validity(uint32_t **map, int rows, int cols,
		t_ivec2 *player_pos);

#endif
