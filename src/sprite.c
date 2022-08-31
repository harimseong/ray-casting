#include "sprite.h"
#include "MLX42.h"
#include "cub3d.h"

#include <stdio.h>

static void	load_distance(t_mlx_data *mlx_data);
//static void print_sprite_info(t_dlist *sprite_list);
static void	draw_sprite(t_mlx_data *mlx_data, t_sprite *sprite,
		const double *depth_buffer);
void	draw_sprite_col_line(t_mlx_data *mlx_data,
		mlx_texture_t *sprite, int32_t idx, int32_t texture_pos);

static const int 	g_ray_cnt = RAY_CNT;
static const int32_t	g_canvas_dist = 4 * PLAYER_SIZE;

void	render_sprite(t_mlx_data *mlx_data, const double *depth_buffer, int size)
{
	t_node		*sprite_node;

	(void)depth_buffer;
	(void)size;
	load_distance(mlx_data);
	dlist_mergesort(&mlx_data->sprite_list, compare);
//	print_sprite_info(&mlx_data->sprite_list);
	sprite_node = mlx_data->sprite_list.head;
	while (sprite_node != NULL)
	{
		draw_sprite(mlx_data, (t_sprite *)sprite_node->content, depth_buffer);
		sprite_node = sprite_node->next;
	}
}

/*
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
		sprite->distance = sqrt(pow(sprite->x - player.x, 2) +
					pow(sprite->y - player.y, 2));
		sprite_node = sprite_node->next;
	}
}

static void	draw_sprite(t_mlx_data *mlx_data, t_sprite *sprite,
		const double *depth_buffer)
{
	t_vec2	position_diff;
	double	sprite_angle;
	int		idx;
	double	width;
	int32_t	mid;
	t_player	*player;

	player = &mlx_data->player;
	position_diff = (t_vec2){sprite->x - player->x, sprite->y - player->y};
	sprite_angle = atan2(position_diff.y, position_diff.x) + M_PI_2;
	if (sprite_angle < 0)
		sprite_angle += 2 * M_PI;
//	-M_PI <= angle < M_PI

	mid = g_ray_cnt * (sprite_angle - player->angle + 0.5 * FOV) / FOV;
	/*
	sprite_start_angle = sprite_start_angle - GRID_LEN * 0.5 * g_canvas_dist / sprite->distance;
	sprite_end_angle = sprite_start_angle + GRID_LEN * g_canvas_dist / sprite->distance;
	width = (sprite_end_angle - sprite_start_angle) * g_ray_cnt / (sprite_end_angle - sprite_start_angle) * 0.5;
	angle_diff = FOV / g_ray_cnt;
	*/
	width = 200 * g_canvas_dist / sprite->distance;
	idx = mid - width;
	while (idx < mid + width)
	{
		if (idx < 0 || idx >= g_ray_cnt || depth_buffer[idx] < sprite->distance)
		{
			++idx;
			continue ;
		}
		draw_sprite_col_line(mlx_data, sprite->texture[sprite->idx], idx,
			(idx + width) / (2 * width) * sprite->texture[sprite->idx]->width);
		++idx;
	}
	sprite->idx = (sprite->idx + 1) % sprite->size;
}

void	draw_sprite_col_line(t_mlx_data *mlx_data,
		mlx_texture_t *sprite, int32_t idx, int32_t texture_pos)
{
	int32_t	y;
	uint32_t	color;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		color = *((uint32_t *)sprite->pixels
			+ y * sprite->width + texture_pos);
		mlx_put_pixel(mlx_data->main_img, 2 * idx, y, color);
		mlx_put_pixel(mlx_data->main_img, 2 * idx + 1, y, color);
		++y;
	}
}
