CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = cub3D
ROOT = mandatory
MLX_DIR = minilibx-linux
INCLUDES = -I $(ROOT)/includes -I $(MLX_DIR)
MLX_FLAGS = -L $(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

SRCS = $(ROOT)/src/main.c \
	$(ROOT)/src/parse/parse_file.c \
	$(ROOT)/src/parse/parse_elements.c \
	$(ROOT)/src/parse/parse_color.c \
	$(ROOT)/src/parse/parse_map.c \
	$(ROOT)/src/parse/validate_map.c \
	$(ROOT)/src/parse/parse_utils.c \
	$(ROOT)/src/parse/parse_utils2.c \
	$(ROOT)/src/parse/ft_split.c \
	$(ROOT)/src/render/raycaster.c \
	$(ROOT)/src/render/calc_wall.c \
	$(ROOT)/src/render/render.c \
	$(ROOT)/src/render/textures.c \
	$(ROOT)/src/input/input.c \
	$(ROOT)/src/input/movement.c \
	$(ROOT)/src/input/rotation.c \
	$(ROOT)/src/utils/utils.c \
	$(ROOT)/src/utils/cleanup.c \
	$(ROOT)/src/utils/init.c

OBJS = $(SRCS:.c=.o)

NAME_BONUS = cub3D_bonus
ROOT_BONUS = bonus
INCLUDES_BONUS = -I $(ROOT_BONUS)/includes -I $(MLX_DIR)
MLX_FLAGS_BONUS = -L $(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm

SRCS_BONUS = $(ROOT_BONUS)/src/main_bonus.c \
	$(ROOT_BONUS)/src/parse/parse_file_bonus.c \
	$(ROOT_BONUS)/src/parse/parse_elements_bonus.c \
	$(ROOT_BONUS)/src/parse/parse_color_bonus.c \
	$(ROOT_BONUS)/src/parse/parse_map_bonus.c \
	$(ROOT_BONUS)/src/parse/validate_map_bonus.c \
	$(ROOT_BONUS)/src/parse/parse_utils_bonus.c \
	$(ROOT_BONUS)/src/parse/parse_utils2_bonus.c \
	$(ROOT_BONUS)/src/parse/ft_split_bonus.c \
	$(ROOT_BONUS)/src/render/raycaster_bonus.c \
	$(ROOT_BONUS)/src/render/calc_wall_bonus.c \
	$(ROOT_BONUS)/src/render/render_bonus.c \
	$(ROOT_BONUS)/src/render/textures_bonus.c \
	$(ROOT_BONUS)/src/input/input_bonus.c \
	$(ROOT_BONUS)/src/input/movement_bonus.c \
	$(ROOT_BONUS)/src/input/rotation_bonus.c \
	$(ROOT_BONUS)/src/utils/utils_bonus.c \
	$(ROOT_BONUS)/src/utils/cleanup_bonus.c \
	$(ROOT_BONUS)/src/utils/init_bonus.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)


all: $(NAME)

$(NAME): $(MLX_DIR)/libmlx_Linux.a $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ cub3D built"

$(MLX_DIR)/libmlx_Linux.a:
	@make -C $(MLX_DIR) -f Makefile.mk -s >/dev/null 2>&1 || true

%.o: %.c $(ROOT)/includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


bonus: $(NAME_BONUS)

$(NAME_BONUS): $(MLX_DIR)/libmlx_Linux.a $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX_FLAGS_BONUS) -o $(NAME_BONUS)
	@echo "✅ cub3D_bonus built"

$(ROOT_BONUS)/%.o: $(ROOT_BONUS)/%.c $(ROOT_BONUS)/includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@


clean:
	@echo "🧹 Cleaning objects..."
	@rm -f $(OBJS) $(OBJS_BONUS)
	@make -C $(MLX_DIR) -f Makefile.mk clean -s 2>/dev/null || true

fclean: clean
	@echo "🗑️  Deep cleaning..."
	@rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
