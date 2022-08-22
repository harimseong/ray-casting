#include "screen_renderer.h"
#include "minimap.h"
//#include "sprite.h"
//#include "raycast.h"

void	screen_renderer(void *data)
{
//	render_main_img((t_mlx_data *)data);
//	render_sprite((t_mlx_data *)data);
	render_minimap((t_mlx_data *)data);
}
