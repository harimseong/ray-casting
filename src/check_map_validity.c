/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:44:09 by hseong            #+#    #+#             */
/*   Updated: 2022/08/22 14:47:31 by soum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_map.h"

enum e_map_element
{
	WALL = '1',
	DOOR = '3',
	EMPTY = '0',
	CHECKED = 0b10000000
};

static int	check_closed(char **map, t_ivec2 pos, t_ivec2 *boundary);
static void	unmask_map(char **map, int rows, int cols);

/*
 * return value 1: FAIL, 0: SUCCESS
 * return value of check_closed()
 * 		1: SUCCESS, 0:FAIL
 */
int	check_map_validity(char **map, int rows, int cols)
{
	int		i;
	int		j;
	t_ivec2	boundary;
	int		ret;

	boundary = (t_ivec2){cols, rows};
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				ret = !check_closed(map, (t_ivec2){j, i}, &boundary);
				unmask_map(map, rows, cols);
				return (ret);
			}
			++j;
		}
		++i;
	}
	return (1);
}

static int	check_closed(char **map, t_ivec2 pos, t_ivec2 *boundary)
{
	if (pos.y < 0 || pos.y >= boundary->y || pos.x < 0 || pos.x >= boundary->x
		|| map[pos.y][pos.x] == ' ')
		return (0);
	if (map[pos.y][pos.x] & CHECKED || map[pos.y][pos.x] == WALL)
		return (1);
	map[pos.y][pos.x] |= CHECKED;
	return (check_closed(map, (t_ivec2){pos.x - 1, pos.y - 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x, pos.y - 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x + 1, pos.y - 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x - 1, pos.y}, boundary)
		&& check_closed(map, (t_ivec2){pos.x + 1, pos.y}, boundary)
		&& check_closed(map, (t_ivec2){pos.x - 1, pos.y + 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x, pos.y + 1}, boundary)
		&& check_closed(map, (t_ivec2){pos.x + 1, pos.y + 1}, boundary));
}

static void	unmask_map(char **map, int rows, int cols)
{
	int		i;
	int		j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			map[i][j] &= 0b01111111;
			if (map[i][j] == ' ')
				map[i][j] = '1';
			++j;
		}
		++i;
	}
}
