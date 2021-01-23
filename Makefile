NAME		= cub3D

SRC			= main.c
OBJ			= $(SRC:.c=.o)

ifeq ($(shell uname),Linux)
MLX_DIR		= ./minilibx-linux
MLX_NAME	= libmlx.a
MLX_FLAGS	= -lmlx -lXext -lX11 -lm
CFLAGS		= -Wall -Wextra -Werror -D LINUX
else
MLX_DIR		= ./newmlx
MLX_NAME	= libmlx.dylib
MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit -lz
CFLAGS		= -Wall -Wextra -Werror
endif
MLX_PATH	= $(MLX_DIR)/$(MLX_NAME)
DEBUG		= -g

CC			= gcc

all:		$(NAME)

$(NAME):	$(OBJ)
			cp $(MLX_PATH) .
			$(CC) $(CFLAGS) $(OBJ) $(DEBUG) -L. $(MLX_FLAGS) -o $(NAME)
			@echo "\x1b[32m[=== Make Done ===]"

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(MLX_NAME)
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re