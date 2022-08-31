#ifndef SPRITE_H
# define SPRITE_H

# include <math.h>

# include "cub3d.h"
# include "player_move.h"
# include "dlinkedlist.h"

# define MAX_SPRITE_TEXTURE (8)

typedef struct s_sprite
{
	mlx_texture_t	**texture;
	int				size;
	int				idx;
	double			x;
	double			y;
	double			distance;
}	t_sprite;

void		render_sprite(t_mlx_data *mlx_data, const double *depth_buffer,
	int size);
uint32_t	get_sprite_color(t_mlx_data *data, t_ray *point, int32_t y);
int 		compare(const void* comp1, const void* comp2);

#endif
