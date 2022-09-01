#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>

# include "MLX42.h"
# include "MLX42_Input.h"
# include "libft.h"
# include "dlinkedlist.h"

# define SCREEN_WIDTH (2560)
# define SCREEN_HEIGHT (1440)
# define SCREEN_TITLE ("cub3d")

# define GRID_LEN (512)
# define FOV (M_PI / 3)
# define RAY_CNT (SCREEN_WIDTH / 2)
# define RAY_TO_PIXEL (SCREEN_WIDTH / RAY_CNT)

# define EAST (0)
# define WEST (1)
# define SOUTH (2)
# define NORTH (3)
# define DOOR (4)

//		  0123  4567  89		31
// type: [0000][0000][0000...0000]
// 0123 : type
// 4567 : door & sprite
# define TYPE_BITMASK (0xf)
# define TYPE_BITSHIFT (4)
# define SPECIAL_TYPE_BITMASK (0xf0)
# define INFO_BITMASK (0xffff0000)
# define INFO_BITSHIFT (16)

enum e_map_value_list
{
	MAP_EMPTY = 0,
	MAP_WALL = 1,
	MAP_DOOR_OPENED = 16,
	MAP_DOOR_CLOSED = 17,
	MAP_SPRITE_NONBLOCK = 32,
	MAP_SPRITE_BLOCK = 33,
};

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
	uint32_t	**map;
	int			width;
	int			height;
}	t_map;

typedef struct s_texture_list
{
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	mlx_texture_t	*wall[4];
	mlx_texture_t	*door;
	mlx_texture_t	*barrel;
	mlx_texture_t	*pillar;
	mlx_texture_t	*light;
	mlx_texture_t	*gun[3];
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
	mlx_image_t		*gun_img;
	mlx_image_t		*ammo_img;
	int				gun_ammo;
	t_map			map;
	t_player		player;
	t_texture_list	texture_list;
	t_dlist			sprite_list;
}	t_mlx_data;

#endif
