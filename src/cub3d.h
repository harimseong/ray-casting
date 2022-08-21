#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>

# include "MLX42.h"
# include "libft.h"

# define SCREEN_WIDTH (2560)
# define SCREEN_HEIGHT (1440)
# define SCREEN_TITLE ("cub3d")

# define MAP_EAST (0)
# define MAP_WEST (1)
# define MAP_SOUTH (2)
# define MAP_NORTH (3)

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture_list
{
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	mlx_texture_t	*wall[4];
	mlx_texture_t	*door;
}	t_texture_list;

typedef struct s_mlx_data
{
	mlx_t			*mlx_ptr;
	t_map			map;
	t_texture_list	texture_list;
}	t_mlx_data;

int init_data(int argc, char** argv, t_mlx_data* mlx_data);

#endif
