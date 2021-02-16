NAME		= cub3D

SRCDIR		= ./srcs/
SRC			= $(SRCDIR)main.c \
				$(SRCDIR)info.c \
				$(SRCDIR)close.c \
				$(SRCDIR)draw.c \
				$(SRCDIR)exit.c \
				$(SRCDIR)exit_sub.c \
				$(SRCDIR)key_press.c \
				$(SRCDIR)key_update.c \
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
				$(SRCDIR)calc/wall_casting_sub.c \
				$(SRCDIR)calc/sprite_casting.c \
				$(SRCDIR)calc/sprite_casting_sub.c \
				$(SRCDIR)utils/bitmap.c \
				$(SRCDIR)utils/get_line.c \
				$(SRCDIR)utils/util.c
OBJ			= $(SRC:.c=.o)

BNSDIR		= ./srcs_bonus/
BNS_SRC		= $(BNSDIR)main_bonus.c \
				$(BNSDIR)info_bonus.c \
				$(BNSDIR)close_bonus.c \
				$(BNSDIR)draw_bonus.c \
				$(BNSDIR)exit_bonus.c \
				$(BNSDIR)exit_sub_bonus.c \
				$(BNSDIR)key_press_bonus.c \
				$(BNSDIR)key_update_bonus.c \
				$(BNSDIR)sprite_list_bonus.c \
				$(BNSDIR)file/cubfile_bonus.c \
				$(BNSDIR)file/file_util_bonus.c \
				$(BNSDIR)file/get_settings_bonus.c \
				$(BNSDIR)file/get_textures_bonus.c \
				$(BNSDIR)file/get_textures_bonus2.c \
				$(BNSDIR)file/get_textures_sub_bonus.c \
				$(BNSDIR)file/get_resolution_bonus.c \
				$(BNSDIR)file/map_bonus.c \
				$(BNSDIR)file/map_validation_bonus.c \
				$(BNSDIR)calc/calc_bonus.c \
				$(BNSDIR)calc/floor_casting_bonus.c \
				$(BNSDIR)calc/wall_casting_bonus.c \
				$(BNSDIR)calc/wall_casting_sub_bonus.c \
				$(BNSDIR)calc/sprite_casting_bonus.c \
				$(BNSDIR)calc/sprite_casting_sub_bonus.c \
				$(BNSDIR)utils/bitmap_bonus.c \
				$(BNSDIR)utils/get_line_bonus.c \
				$(BNSDIR)utils/util_bonus.c
BNS_OBJ		= $(BNS_SRC:.c=.o)

INCLUDE 	= -I./includes/ \
				-I./libft/ \
				-I./includes_bonus/

LIBDIR		= ./libft
LIBPATH		= $(LIBDIR)/libft.a

ifeq ($(shell uname),Linux)
MLX_DIR		= ./minilibx-linux
MLX_NAME	= libmlx.a
MLX_FLAGS	= -lmlx -lXext -lX11 -lm
CFLAGS		= -Wall -Wextra -Werror -D LINUX
C_GREEN		= "\e[32m"
else
MLX_DIR		= ./minilibx_mms_20200219
MLX_NAME	= libmlx.dylib
MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit -lz
CFLAGS		= -Wall -Wextra -Werror
C_GREEN		= "\x1b[32m"
endif
MLX_PATH	= $(MLX_DIR)/$(MLX_NAME)
INCLUDE		+= -I$(MLX_DIR)

DEBUG		=
CC			= gcc

.c.o:
			$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ) $(LIBPATH) $(MLX_PATH)
			cp $(MLX_PATH) .
			$(CC) $(CFLAGS) $(OBJ) $(DEBUG) -L. $(MLX_FLAGS) $(LIBPATH) -o $(NAME)
			@echo $(C_GREEN)"=== Make Done ==="

bonus:		$(BNS_OBJ) $(LIBPATH) $(MLX_PATH)
			cp $(MLX_PATH) .
			$(CC) $(CFLAGS) $(BNS_OBJ) $(DEBUG) -L. $(MLX_FLAGS) $(LIBPATH) -o $(NAME)
			@echo $(C_GREEN)"=== Make Done ==="

$(LIBPATH):
			$(MAKE) -C $(LIBDIR)

$(MLX_PATH):
			$(MAKE) -C $(MLX_DIR)

clean:
			$(MAKE) clean -C $(LIBDIR)
			$(MAKE) clean -C $(MLX_DIR)
			$(RM) $(OBJ)
			$(RM) $(BNS_OBJ)

fclean:		clean
			$(MAKE) fclean -C $(LIBDIR)
			$(RM) $(MLX_NAME)
			$(RM) $(NAME)

re:			fclean $(NAME)

mlx:
ifeq ($(shell uname),Linux)
			git clone https://github.com/42Paris/minilibx-linux.git
			cd minilibx-linux
			git checkout db799639c0ede85470691d837fdaf1cb5a375eba
else
			curl -O https://projects.intra.42.fr/uploads/document/document/2717/minilibx_mms_20200219_beta.tgz
			tar -xvf minilibx_mms_20200219_beta.tgz
endif

delmlx:
			rm -rf $(MLX_DIR)

.PHONY:		all clean fclean re bonus mlx delmlx
