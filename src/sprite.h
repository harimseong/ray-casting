#ifndef SPRITE_H
# define SPRITE_H

# include <math.h>

# include "cub3d.h"
# include "dlinkedlist.h"
# include "raycasting.h"
# include "player_move.h"

# define SPRITE_WIDTH (256)
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
uint32_t	get_sprite_color(t_sprite *sprite, int32_t pos, int32_t y);
int			compare(const void *comp1, const void *comp2);

#endif
