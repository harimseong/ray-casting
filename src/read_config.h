#ifndef READ_CONFIG_H
# define READ_CONFIG_H

#include "cub3d.h"
#include "error.h"
#include "get_next_line.h"
#include "garbage_collector/garbage_collector.h"

# define TEXTURE_LIST_NUM (7)
# define ALL_OPTION_FILLED (0b1111111)

void	get_config_info(int fd, t_mlx_data *mlx_data);
int		check_config_path(const char *path);
int		is_map(const char *read_line);
void	free_splited_arr(char **splited_words);
int		count_splited_words(char **splited_words);
char*	sub_newline(char *read_line);

#endif
