NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes -I minilibx-linux
MLX_DIR = minilibx-linux
MLX_FLAGS = -L $(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

SRCS = src/main.c \
       src/parse/parse_file.c \
       src/parse/parse_elements.c \
       src/parse/parse_color.c \
       src/parse/parse_map.c \
       src/parse/validate_map.c \
       src/parse/parse_utils.c \
       src/parse/parse_utils2.c \
       src/parse/ft_split.c \
       src/render/raycaster.c \
       src/render/calc_wall.c \
       src/render/render.c \
       src/render/textures.c \
       src/input/input.c \
       src/input/movement.c \
       src/input/rotation.c \
       src/utils/utils.c \
       src/utils/cleanup.c \
       src/utils/init.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(MLX_DIR)/libmlx_Linux.a:
	@make -C $(MLX_DIR) -f Makefile.mk -s >/dev/null 2>&1 || true

$(NAME): $(MLX_DIR)/libmlx_Linux.a $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Build completed"

%.o: %.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "🧹 Cleaning objects..."
	@rm -f $(OBJS)
	@make -C $(MLX_DIR) -f Makefile.mk clean -s 2>/dev/null || true

fclean: clean
	@echo "🗑️  Deep cleaning..."
	@rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
