NAME	=	cub3d


CC		=	cc
#CFLAGS	=	-Wall -Wextra -Werror
DEBUG	=	-g3 -fsanitize=address -DDEBUG_FLAG=1
RM		=	rm -f

SRC		=	main.c\
			get_next_line.c\
			get_next_line_utils.c

SRC		:=	$(SRC:%=src/%)
OBJ		=	$(SRC:%.c=%.o)

INC_DIR	=


LIBFLAGS 	+=	-L.

# NOTE: library order (-ldlinkedlist and -lft) can be problem
LIBFLAGS 	+=	-ldlinkedlist
DLLIST		=	libdlinkedlist.a
DLLIST_DIR	=	doubly_linked_list
LIBRARYS	+=	DLLIST.lib
INC_DIR		+=	-I$(DLLIST_DIR)


LIBFLAGS 	+=	-lft
LIBFT		=	libft.a
LIBFT_DIR	=	libft
LIBRARYS 	+=	LIBFT.lib
INC_DIR		+=	-I$(LIBFT_DIR)


LIBFLAGS	+= -lmlx42
MLX42		=	libmlx42.a
MLX42_DIR	=	mlx42
LIBRARYS	+=	MLX42.lib
INC_DIR		+=	-I$(MLX42_DIR)/include/MLX42
ifeq ($(shell uname), Darwin)
LIBFLAGS	+= -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
else
LIBFLAGS	+= -ldl -lglfw3 -pthread -lm
endif


ifeq ($(DEBUG_FLAG), 1)
CFLAGS			+=	$(DEBUG)
LIB_DEBUG_FLAG	=	DEBUG_FLAG=1
COMPILE			=	DEBUG.flag
else
COMPILE			=	RELEASE.flag
endif


libs: $(COMPILE) $(LIBRARYS)
	$(MAKE) $(NAME)

all: $(NAME)

debug: 
	$(MAKE) DEBUG_FLAG=1 libs

RELEASE.flag:
	$(MAKE) fclean
	touch RELEASE.flag

DEBUG.flag:
	$(MAKE) fclean
	touch DEBUG.flag

$(LIBRARYS): %.lib:
	$(MAKE) -C $($*_DIR) $(LIB_DEBUG_FLAG) all
	@cp -p $($*_DIR)/$($*) .

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBFLAGS)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INC_DIR)

clean:
	$(RM) $(OBJ)
	$(RM) DEBUG.flag RELEASE.flag

fclean: clean $(LIBRARYS:%=%.clean)
	$(RM) $($(LIBRARYS:%.lib=%))
	$(RM) $(NAME)

$(LIBRARYS:%=%.clean): %.lib.clean:
	$(RM) $($*)
	@$(MAKE) -C $($*_DIR) fclean
	$(RM) $*.lib

re: fclean
	$(MAKE) libs

.PHONY: all clean fclean re libs
