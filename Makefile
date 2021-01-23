NAME		= cub3D

SRCDIR		= ./srcs/
SRC			= main.c \
				$(SRCDIR)key.c \
				$(SRCDIR)sprite_list.c \
				$(SRCDIR)utils/get_line.c \
				$(SRCDIR)utils/util.c
OBJ			= $(SRC:.c=.o)

INCLUDE 	= -I./includes/ \
				-I./libft/

LIBDIR		= ./libft
LIBPATH		= $(LIBDIR)/libft.a

ifeq ($(shell uname),Linux)
MLX_DIR		= ./minilibx-linux
MLX_NAME	= libmlx.a
MLX_FLAGS	= -lmlx -lXext -lX11 -lm
CFLAGS		= -Wall -Wextra -Werror -D LINUX
C_GREEN		= "\e[32m"
else
MLX_DIR		= ./newmlx
MLX_NAME	= libmlx.dylib
MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit -lz
CFLAGS		= -Wall -Wextra -Werror
C_GREEN		= "\x1b[32m"
endif
MLX_PATH	= $(MLX_DIR)/$(MLX_NAME)
INCLUDE		+= -I$(MLX_DIR)

DEBUG		= -g
CC			= gcc

.c.o:
			$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBPATH)
			cp $(MLX_PATH) .
			$(CC) $(CFLAGS) $(OBJ) $(DEBUG) -L. $(MLX_FLAGS) $(LIBPATH) -o $(NAME)
			@echo $(C_GREEN)"=== Make Done ==="

$(LIBPATH):
			$(MAKE) -C $(LIBDIR)

clean:
			$(MAKE) clean -C $(LIBDIR)
			$(RM) $(OBJ)

fclean:		clean
			$(MAKE) fclean -C $(LIBDIR)
			$(RM) $(MLX_NAME)
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re