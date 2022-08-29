#ifndef USER_INTERFACE_H
# define USER_INTERFACE_H

# include <sys/time.h>
# include <stdio.h>

# include "cub3d.h"

void	user_interface(t_mlx_data *mlx_data);
void	crosshair_line(t_mlx_data *data, int pos, int len);
void	print_frame(void);

#endif
