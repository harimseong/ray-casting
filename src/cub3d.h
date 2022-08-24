#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>

# include "MLX42.h"
# include "libft.h"

# define SCREEN_WIDTH (2560)
# define SCREEN_HEIGHT (1440)
# define SCREEN_TITLE ("cub3d")

# define GRID_LEN (512)

typedef struct s_ivec2
{
	int64_t	x;
	int64_t	y;
}	t_ivec2;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_ray
{
	double	x;
	double	y;
	double	distance;
	int		direction;
} t_ray;

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

typedef struct s_player
{
	double		angle;
	double		x;
	double		y;
	t_ivec2		grid;
}	t_player;

typedef struct s_mlx_data
{
	mlx_t			*mlx_ptr;
	mlx_image_t		*main_img;
	mlx_image_t		*minimap;
	t_map			map;
	t_player		player;
	t_texture_list	texture_list;
}	t_mlx_data;

#endif
