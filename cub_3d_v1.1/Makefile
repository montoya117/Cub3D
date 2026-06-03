# Program name
NAME        = cub3D

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

# 1. Detectar el Sistema Operativo
UNAME_S := $(shell uname -s)

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes
LIBFT_DIR   = libft
MLX_DIR     = minilibx

# Library paths
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

# Includes
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

# 2. Configurar Flags por defecto (Linux)
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

# 3. Modificar Flags si estás en macOS (Darwin)
ifeq ($(UNAME_S), Darwin)
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# Source files
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
				$(SRC_DIR)/sprites/sprites.c\
				$(SRC_DIR)/hooks/handle_key.c \
				$(SRC_DIR)/hooks/move.c \
				$(SRC_DIR)/hooks/move_helpers.c \
				$(SRC_DIR)/hooks/process_movement.c \
                $(SRC_DIR)/graphics/buffer_utils.c \
                $(SRC_DIR)/minimap/draw_minimap.c \
				$(SRC_DIR)/utils/utils_parser.c \
				$(SRC_DIR)/utils/utils_validate.c \
                $(SRC_DIR)/utils/error.c \
				$(SRC_DIR)/utils/free_data.c \
				$(SRC_DIR)/utils/free_graphics.c \
                $(SRC_DIR)/gnl/get_next_line.c \
				$(SRC_DIR)/gnl/gnl_helpers.c \
                $(SRC_DIR)/main.c

OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule
all: $(LIBFT) $(MLX) $(NAME)

# Compile libft (¡Obligando a compilar los BONUS para tener las listas!)
$(LIBFT):
	@echo "Compiling libft con bonus..."
	@make -C $(LIBFT_DIR) bonus

# Compile minilibx
$(MLX):
	@echo "Compiling minilibx..."
	@make -C $(MLX_DIR)

# Link the final executable
$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "¡$(NAME) compilado Vamos!"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean objects
clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

# Clean objects and executables
fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re