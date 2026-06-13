
NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -MMD -MP

UNAME_S := $(shell uname -s)

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes
LIBFT_DIR   = libft
MLX_DIR     = minilibx

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

ifeq ($(UNAME_S), Darwin)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

SRCS        =   $(SRC_DIR)/parser/parser.c \
                $(SRC_DIR)/parser/parser_map.c \
				$(SRC_DIR)/parser/validate.c \
				$(SRC_DIR)/parser/validate_player.c \
				$(SRC_DIR)/parser/validate_helpers.c \
                $(SRC_DIR)/parser/parser_config_textures.c \
                $(SRC_DIR)/parser/parser_config_colors.c \
                $(SRC_DIR)/parser/init.c \
				$(SRC_DIR)/parser/init_helpers.c \
				$(SRC_DIR)/graphics/textures.c \
                $(SRC_DIR)/graphics/init_graphics.c \
                $(SRC_DIR)/graphics/render.c \
                $(SRC_DIR)/graphics/draw.c \
				$(SRC_DIR)/graphics/draw_helpers.c \
				$(SRC_DIR)/graphics/ray_render.c \
				$(SRC_DIR)/hooks/handle_key.c \
				$(SRC_DIR)/hooks/move.c \
				$(SRC_DIR)/hooks/move_helpers.c \
				$(SRC_DIR)/hooks/process_movement.c \
                $(SRC_DIR)/graphics/buffer_utils.c \
				$(SRC_DIR)/utils/utils_parser.c \
				$(SRC_DIR)/utils/utils_validate.c \
                $(SRC_DIR)/utils/error.c \
				$(SRC_DIR)/utils/free_data.c \
				$(SRC_DIR)/utils/free_graphics.c \
                $(SRC_DIR)/gnl/get_next_line.c \
				$(SRC_DIR)/gnl/gnl_helpers.c \
                $(SRC_DIR)/main.c

BONUS_SRCS  =   $(SRC_DIR)/sprites/sprites.c \
                $(SRC_DIR)/minimap/draw_minimap.c

OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_BONUS  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

DEPS        = $(OBJS:.o=.d) $(OBJS_BONUS:.o=.d)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "Compiling libft (bonus)..."
	@$(MAKE) -C $(LIBFT_DIR) OBJ_DIR=obj bonus

$(MLX):
	@if [ -f $(MLX) ]; then \
		echo "minilibx ya existe, se omite compilación."; \
	else \
		echo "Compiling minilibx..."; \
		$(MAKE) -C $(MLX_DIR); \
	fi

$(NAME): $(OBJS) Makefile
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "¡$(NAME) compilado Vamos!"

$(NAME)_bonus: $(OBJS) $(OBJS_BONUS) Makefile
	@echo "Linking $(NAME)_bonus..."
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)_bonus
	@echo "¡$(NAME)_bonus compilado Vamos!"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus:
	@echo "Preparing libraries for bonus build..."
	@$(MAKE) -C $(LIBFT_DIR) OBJ_DIR=obj bonus
	@$(MAKE) -C $(MLX_DIR) OBJ_DIR=obj
	@echo "Building bonus version from src_bonus..."
	@$(MAKE) SRC_DIR=src_bonus OBJ_DIR=obj_bonus $(NAME)_bonus

clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJ_DIR) obj_bonus
	@make -C $(LIBFT_DIR) clean
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME) $(NAME)_bonus
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPS)
