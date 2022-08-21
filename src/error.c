#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "cub3d.h"
#include "error.h"
#include "garbage_collector/garbage_collector.h"

static const char	*g_error_msg_list[] = {
	"invalid argument",
	"filename error",
	"file open error",
	"config format error",
	"config file has duplicate option",
	"there is not enough options",
	"invalid rgb value of floor or ceiling",
	"invalid texture path or name"
};

void	error_handler(int status)
{
	if (status == 0)
		return ;
	ft_putendl_fd(g_error_msg_list[status - 1], STDERR_FILENO);
	dump_garbage();
	exit(status);
}
