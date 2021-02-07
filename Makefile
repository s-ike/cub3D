NAME		= cub3D

SRCDIR		= ./srcs/
SRC			= main.c \
				$(SRCDIR)info.c \
				$(SRCDIR)close.c \
				$(SRCDIR)exit.c \
				$(SRCDIR)exit_sub.c \
				$(SRCDIR)key.c \
				$(SRCDIR)sprite_list.c \
				$(SRCDIR)file/cubfile.c \
				$(SRCDIR)file/file_util.c \
				$(SRCDIR)file/get_settings.c \
				$(SRCDIR)file/get_colors.c \
				$(SRCDIR)file/get_textures.c \
				$(SRCDIR)file/get_textures_sub.c \
				$(SRCDIR)file/get_resolution.c \
				$(SRCDIR)file/map.c \
				$(SRCDIR)file/map_validation.c \
				$(SRCDIR)calc/calc.c \
				$(SRCDIR)calc/floor_casting.c \
				$(SRCDIR)calc/wall_casting.c \
				$(SRCDIR)calc/sprite_casting.c \
				$(SRCDIR)utils/bitmap.c \
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
# TODO: ./newmlx にする
MLX_DIR		= ./mlx
# TODO: libmlx.dylib にする
MLX_NAME	= libmlx.a
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
