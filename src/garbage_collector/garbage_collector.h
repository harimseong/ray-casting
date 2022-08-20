#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

typedef struct s_garbage
{
	int		fd;
	void	*ptr;
	void	**ptr_2d;
}	t_garbage;

t_garbage	*get_garbage_ptr(void);
void	collect_fd_garbage(int fd);
void	collect_ptr_garbage(void *ptr);
void	collect_ptr_2d_garbage(void **ptr_2d);
void	dump_garbage(void);

#endif
