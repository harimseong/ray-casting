#include "sprite.h"
#include "MLX42.h"
#include "init_data.h"

static void	load_distance(t_mlx_data *mlx_data);
static void	draw_sprite(t_mlx_data *mlx_data, t_sprite *sprite,
				t_player *player, const double *depth_buffer);
static void	draw_sprite_col_line(t_mlx_data *mlx_data,
				t_sprite *sprite, int32_t idx, int32_t transfer_ratio);
static void	increment_sprite_idx(t_sprite *sprite);

void	render_sprite(t_mlx_data *mlx_data, const double *depth_buffer,
		int size)
{
	t_node		*sprite_node;

	(void)depth_buffer;
	(void)size;
	load_distance(mlx_data);
	dlist_mergesort(&mlx_data->sprite_list, compare);
	sprite_node = mlx_data->sprite_list.head;
	while (sprite_node != NULL)
	{
		draw_sprite(mlx_data, (t_sprite *)sprite_node->content,
			&mlx_data->player, depth_buffer);
		sprite_node = sprite_node->next;
	}
}

/*
static void print_sprite_info(t_dlist *sprite_list);

static void print_sprite_info(t_dlist *sprite_list)
{
	size_t		idx;
	t_node		*sprite_node;
	t_sprite	*sprite;

	idx = 0;
	sprite_node = sprite_list->head;
	while (sprite_node)
	{
		sprite = sprite_node->content;
		printf("idx : %zu sprite x : %f y : %f distance : %f\n",
				idx, sprite->x, sprite->y, sprite->distance);
		sprite_node = sprite_node->next;
		++idx;
	}
}
*/
static void	load_distance(t_mlx_data *mlx_data)
{
	t_player	player;
	t_node		*sprite_node;
	t_sprite	*sprite;

	player = mlx_data->player;
	sprite_node = mlx_data->sprite_list.head;
	while (sprite_node)
	{
		sprite = sprite_node->content;
		sprite->distance = sqrt(pow(sprite->x - player.x, 2)
				+ pow(sprite->y - player.y, 2));
		sprite_node = sprite_node->next;
	}
}

static void	draw_sprite(t_mlx_data *mlx_data, t_sprite *sprite,
		t_player *player, const double *depth_buffer)
{
	double		angle;
	int			idx;
	int			width;
	int32_t		mid;

	angle = atan2(sprite->y - player->y, sprite->x - player->x) + M_PI_2;
	if (angle < 0)
		angle += 2 * M_PI;
	angle -= player->angle;
	mid = g_ray_cnt * (angle + 0.5 * g_fov) / g_fov;
	if (angle > 2 * M_PI - M_PI_2)
		mid = g_ray_cnt * (angle - 2 * M_PI + 0.5 * g_fov) / g_fov;
	else if (angle < 2 * M_PI - M_PI_2)
		mid = g_ray_cnt * (angle + 2 * M_PI + 0.5 * g_fov) / g_fov;
	width = SPRITE_WIDTH * g_canvas_dist / sprite->distance;
	idx = mid - width;
	while (idx < mid + width)
	{
		if (idx >= 0 && idx < g_ray_cnt && depth_buffer[idx] > sprite->distance)
			draw_sprite_col_line(mlx_data, sprite, idx,
				(double)(idx - mid + width) / (2.0 * width));
		++idx;
	}
	increment_sprite_idx(sprite);
}

void	draw_sprite_col_line(t_mlx_data *mlx_data, t_sprite *sprite,
		int32_t idx, int32_t transfer_ratio)
{
	int32_t			pixel_y;
	int32_t			texture_x_pos;
	uint32_t		color;
	mlx_texture_t	*texture;

	pixel_y = 0;
	texture = sprite->texture[sprite->idx];
	texture_x_pos = texture->width * transfer_ratio;
	while (pixel_y < SCREEN_HEIGHT)
	{
		color = get_sprite_color(sprite, texture_x_pos, pixel_y);
		if (color != 0)
		{
			mlx_put_pixel(mlx_data->main_img, 2 * idx, pixel_y, color);
			mlx_put_pixel(mlx_data->main_img, 2 * idx + 1, pixel_y, color);
		}
		++pixel_y;
	}
}

static void	increment_sprite_idx(t_sprite *sprite)
{
	static uint32_t	frame;

	if (frame % 10)
		++sprite->idx;
	++frame;
}

void init_sprite_texture(t_mlx_data *mlx_data)
{
	mlx_data->texture_list.barrel = mlx_load_png(BARREL_SPRITE_TEXTURE);
	mlx_data->texture_list.light = mlx_load_png(LIGHT_SPRITE_TEXTURE);
	mlx_data->texture_list.pillar = mlx_load_png(PILLAR_SPRITE_TEXTURE);
	mlx_data->texture_list.gun[0] = mlx_load_png(GUN_SPRITE_TEXTURE_1);
	mlx_data->texture_list.gun[1] = mlx_load_png(GUN_SPRITE_TEXTURE_2);
	mlx_data->texture_list.gun[2] = mlx_load_png(GUN_SPRITE_TEXTURE_3);
	mlx_data->texture_list.enemy[0] = mlx_load_png(ENEMY_SPRITE_TEXTURE_1);
	mlx_data->texture_list.enemy[1] = mlx_load_png(ENEMY_SPRITE_TEXTURE_2);
	mlx_data->texture_list.enemy[2] = mlx_load_png(ENEMY_SPRITE_TEXTURE_3);
	mlx_data->texture_list.enemy[3] = mlx_load_png(ENEMY_SPRITE_TEXTURE_4);
	mlx_data->texture_list.enemy[4] = mlx_load_png(ENEMY_SPRITE_TEXTURE_5);
	mlx_data->texture_list.enemy[5] = mlx_load_png(ENEMY_SPRITE_TEXTURE_6);
	mlx_data->texture_list.enemy[6] = mlx_load_png(ENEMY_SPRITE_TEXTURE_7);
	mlx_data->texture_list.enemy[7] = mlx_load_png(ENEMY_SPRITE_TEXTURE_8);
}
