#ifndef ERROR_H
# define ERROR_H

enum e_error_status
{
	NONE,
	ARGUMENT_ERROR,
	FILENAME_ERROR,
	FILE_OPEN_ERROR,
	CONFIG_FORMAT_ERROR,
	CONFIG_DUPLICATE_ERROR,
	CONFIG_NOT_ENOUGH_OPTION_ERROR,
	CONFIG_INVALID_RGB_ERROR,
};

void	error_handler(int status);

#endif
