# Program name
NAME        = cub3D

# Compiler and Flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

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

# Source files (sin archivos de bonus: sprites/minimap)
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

# Bonus source files (relativos a $(SRC_DIR))
BONUS_SRCS  =   $(SRC_DIR)/sprites/sprites.c \
                $(SRC_DIR)/minimap/draw_minimap.c

OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS_BONUS  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

# Default rule
all: $(LIBFT) $(MLX) $(NAME)

# Compile libft:
# - Forzamos compilación del bonus en libft pero evitando que herede OBJ_DIR=obj_bonus:
$(LIBFT):
	@echo "Compiling libft (bonus)..."
	@$(MAKE) -C $(LIBFT_DIR) OBJ_DIR=obj bonus

# Compile minilibx:
# - Forzamos compilación en su carpeta normal (OBJ_DIR=obj) para que siempre genere libmlx.a con el nombre esperado
$(MLX):
	@if [ -f $(MLX) ]; then \
		echo "minilibx ya existe, se omite compilación."; \
	else \
		echo "Compiling minilibx..."; \
		$(MAKE) -C $(MLX_DIR); \
	fi

# Link the final executable (sin bonus)
$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "¡$(NAME) compilado Vamos!"

# Link the bonus executable (normal + bonus sources)
# OBS: OBJS and OBJS_BONUS are evaluated using current $(SRC_DIR)/$(OBJ_DIR)
$(NAME)_bonus: $(OBJS) $(OBJS_BONUS)
	@echo "Linking $(NAME)_bonus..."
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)_bonus
	@echo "¡$(NAME)_bonus compilado Vamos!"

# Compile source files to object files
# This pattern works whether OBJ_DIR/ and SRC_DIR are normal or the *_bonus versions passed by recursive make
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# -------------------------
# BONUS target (usa src_bonus)
# -------------------------
# Prepara las bibliotecas en su modo "normal" (pero con libft en bonus),
# y luego lanza la build recursiva apuntando a src_bonus/ y obj_bonus/
.PHONY: bonus
bonus:
	@echo "Preparing libraries for bonus build..."
	@$(MAKE) -C $(LIBFT_DIR) OBJ_DIR=obj bonus
	@$(MAKE) -C $(MLX_DIR) OBJ_DIR=obj
	@echo "Building bonus version from src_bonus..."
	@$(MAKE) SRC_DIR=src_bonus OBJ_DIR=obj_bonus $(NAME)_bonus

# Clean objects (incluye obj_bonus)
clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJ_DIR) obj_bonus
	@make -C $(LIBFT_DIR) clean
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

# Clean objects and executables
fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME) $(NAME)_bonus
	@make -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re bonus
