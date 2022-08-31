#include "sprite.h"
#include "dlinkedlist.h"

#include <stdio.h>

static void	load_distance(t_mlx_data *mlx_data);
int compare(const void* comp1, const void* comp2);
static void print_sprite_info(t_dlist *sprite_list);

void	render_sprite(t_mlx_data *mlx_data, const double *depth_buffer, int size)
{
	(void)depth_buffer;
	(void)size;
	load_distance(mlx_data);
	dlist_mergesort(&mlx_data->sprite_list, compare);
	print_sprite_info(&mlx_data->sprite_list);
}

static void print_sprite_info(t_dlist *sprite_list)
{
	size_t		idx;
	t_node		*sprite_node;
	t_sprite	*sprite;

	/** dlist_mergesort(sprite_list, compare); */
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

int compare(const void* comp1, const void* comp2)
{
	if (((t_sprite*)comp1)->distance < ((t_sprite*)comp2)->distance)
		return (1);
	return (-1);
}
