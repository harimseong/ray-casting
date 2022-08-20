/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub_file_option.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soum <soum@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 14:28:22 by soum              #+#    #+#             */
/*   Updated: 2022/08/20 19:14:46 by hseong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_text_to_null(t_mlx_data *data)
{
	t_texture	*text;

	text = &data->texture;
	text->ceiling_txt = NULL;
	text->floor_txt = NULL;
	text->n_wall_path = NULL;
	text->s_wall_path = NULL;
	text->e_wall_path = NULL;
	text->w_wall_path = NULL;
}

int	check_read_line(char *read_line, t_mlx_data *data)
{
	if (read_line[0] == '\n')
		return (0);
	if (ft_strnstr(read_line, "NO ", ft_strlen(read_line)))
		return (load_option(data, "NO ", read_line));
	else if (ft_strnstr(read_line, "SO ", ft_strlen(read_line)))
		return (load_option(data, "SO ", read_line));
	else if (ft_strnstr(read_line, "WE ", ft_strlen(read_line)))
		return (load_option(data, "WE ", read_line));
	else if (ft_strnstr(read_line, "EA ", ft_strlen(read_line)))
		return (load_option(data, "EA ", read_line));
	else if (ft_strnstr(read_line, "F ", ft_strlen(read_line)))
		return (2 * load_option(data, "F ", read_line));
	else if (ft_strnstr(read_line, "C ", ft_strlen(read_line)))
		return (2 * load_option(data, "C ", read_line));
	return (4);
}

void	check_file_option_vaild(t_mlx_data *data)
{
	int		fd;
	char	*read_line;
	int		check;

	fd = open(data->map.map_path, O_RDONLY);
	if (fd < 0)
		error_msg("file open error", FILE_OPEN_ERROR, data);
	while (1)
	{
		read_line = get_next_line(fd);
		if (!read_line || map_check(read_line))
			break ;
		check = check_read_line(read_line, data);
		if (check == 1)
			error_msg("wall texture duplicated!", OPTION_INIT_ERROR, data);
		else if (check == 2)
			error_msg("floor / ceiling data is unvailable or duplicated", \
					OPTION_INIT_ERROR, data);
		free(read_line);
	}
	free(read_line);
	close(fd);
}

void	is_all_option_load(t_mlx_data *data)
{
	t_texture	all_text;

	all_text = data->texture;
	if (!all_text.n_wall_path)
		error_msg("north wall path is empty", OPTION_INIT_ERROR, data);
	if (!all_text.s_wall_path)
		error_msg("south wall path is empty", OPTION_INIT_ERROR, data);
	if (!all_text.w_wall_path)
		error_msg("west wall path is empty", OPTION_INIT_ERROR, data);
	if (!all_text.e_wall_path)
		error_msg("east wall path is empty", OPTION_INIT_ERROR, data);
	if (!all_text.floor_txt)
		error_msg("floor color is empty", OPTION_INIT_ERROR, data);
	if (!all_text.ceiling_txt)
		error_msg("ceiling color is empty", OPTION_INIT_ERROR, data);
}

void	init_cub_file_option(t_mlx_data *data)
{
	t_texture	*text;

	text = &data->texture;
	init_text_to_null(data);
	check_file_option_vaild(data);
	is_all_option_load(data);
	text->ceiling_color = char_to_color(text->ceiling_txt, data);
	text->floor_color = char_to_color(text->floor_txt, data);
}
