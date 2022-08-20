/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseong <hseong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:57:58 by hseong            #+#    #+#             */
/*   Updated: 2022/07/27 19:03:07 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_check(const char *read_line)
{
	while (*read_line == ' ')
		++read_line;
	if (ft_isdigit(*read_line))
		return (1);
	return (0);
}

int	map_line_check(const char *read_line)
{
	if (read_line == NULL)
		return (1);
	while (*read_line && *read_line != '\n')
	{
		if (!ft_strchr("013NSWE ", *read_line++))
			return (0);
	}
	return (1);
}
