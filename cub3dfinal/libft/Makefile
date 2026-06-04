# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 19:47:03 by alemonto          #+#    #+#              #
#    Updated: 2025/05/13 19:25:01 by alemonto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Library name
NAME    = libft.a

# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Color definitions
RESET      := \033[0m
BOLD_GREEN := \033[1;32m
SOFT_BLUE  := \033[1;34m
BOLD_YELLOW = \033[93m

# Source files
SRCS    = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_tolower.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c ft_toupper.c

# Bonus source files
SRCS_B  = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
	ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

# Add path to sources
SRCS    := $(addprefix $(SRC_DIR)/,$(SRCS))
SRCS_B  := $(addprefix $(SRC_DIR)/,$(SRCS_B))

# Object files
OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_B  = $(SRCS_B:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(NAME)

# Link object files into library
$(NAME): $(OBJS)
	
	@echo "$(SOFT_BLUE)Archiving $(NAME)...$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@echo "$(SOFT_BLUE)+-------------------------------------------------------------------+"
	@echo "$(SOFT_BLUE)| _  _     ___       __       __  .______    _______ .___________.  |"
	@echo "$(SOFT_BLUE)| | || |   |__ \     |  |     |  | |   _  \  |   ____||           | |"
	@echo "$(SOFT_BLUE)| | || |_     ) |    |  |     |  | |  |_)  | |  |__   $(BOLD_YELLOW)\`---|  |----\`$(SOFT_BLUE) |"
	@echo "$(SOFT_BLUE)| |__   _|   / /     |  |     |  | |   _  <  |   __|      |  |      |"
	@echo "$(SOFT_BLUE)|    | |    / /_     |  \`----.|  | |  |_)  | |  |         |  |      |"
	@echo "$(SOFT_BLUE)|    |_|   |____|    |_______||__| |______/  |__|         |__|      |"
	@echo "$(SOFT_BLUE)+-------------------------------------------------------------------+"
	@echo ""
	@echo "$(BOLD_GREEN)✅ Successfully compiled libft!$(RESET)"
	@echo ""

bonus: $(OBJS) $(OBJS_B)
	@echo "$(SOFT_BLUE)Archiving $(NAME) with bonus...$(RESET)"
	@ar rcs $(NAME) $(OBJS) $(OBJS_B)
	@echo "$(BOLD_GREEN)✅ Bonus functions successfully added!$(RESET)"

# Ensure obj/ exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(BOLD_GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "$(BOLD_YELLOW)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	@echo "$(BOLD_YELLOW)Removing $(NAME)$(RESET)"
	@rm -f $(NAME)
	@echo "$(BOLD_GREEN)✅ Full clean completed!$(RESET)"

# Rebuild
re: fclean all

.PHONY: all clean fclean re bonus
