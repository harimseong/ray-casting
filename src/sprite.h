#ifndef SPRITE_H
# define SPRITE_H

# include "cub3d.h"

# define MAX_SPRITE_TEXTURE (8)

typedef struct s_sprite
{
	mlx_texture_t	*texture[MAX_SPRITE_TEXTURE];
	int				size;
	int				idx;
}	t_sprite;

void	render_sprite(t_mlx_data mlx_data, const double *depth_buffer, int size);

#endif
