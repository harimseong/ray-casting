#include "sprite.h"

static const int32_t	g_half_screen_height = SCREEN_HEIGHT / 2;
static const int32_t	g_canvas_dist = 4 * PLAYER_SIZE;

uint32_t	get_sprite_color(t_sprite *sprite, int32_t pos, int32_t y)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	int32_t			range;

	texture = sprite->texture[sprite->idx];
	range = g_canvas_dist * g_half_screen_height / sprite->distance;
	if (-range + g_half_screen_height > y || range + g_half_screen_height <= y)
		return (0);
	y = (y - g_half_screen_height + range) * texture->height / (2 * range);
	color = *((uint32_t *)texture->pixels + \
			((int)y * texture->width + pos));
	color = to_le(color, FOG_FACTOR / (sprite->distance + FOG_FACTOR));
	return (color);
}

int compare(const void* comp1, const void* comp2)
{
	if (((t_sprite*)comp1)->distance < ((t_sprite*)comp2)->distance)
		return (1);
	return (-1);
}
