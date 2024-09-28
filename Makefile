# Program name
NAME		= cub3D

# Compiler
CC			= cc

# Compilation flags
CFLAGS		= -Wall -Wextra -Werror -Wunreachable-code -Ofast

# Include libraries and header files
LIBMLX	= ./MLX42
HEADERS	= -I ./includes -I $(LIBMLX)/include -I $(LIBFT_DIR)
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT = $(LIBFT_DIR)/libft.a

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
LIBFT_DIR 	= libft

# Source files
SRCS		=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/draw_minimap.c \
				$(SRC_DIR)/lines.c \
				$(SRC_DIR)/move_player.c \
				$(SRC_DIR)/read_input.c \
				$(SRC_DIR)/check_input.c \
				$(SRC_DIR)/raycasting.c \
				$(SRC_DIR)/main_img.c 

# Objects
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libmlx $(NAME)

libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Build project
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(LIBFT)
	@echo "$(NAME) built successfully"

# add libmlx
$(LIBMLX):
	@touch .gitmodules
	@git submodule add -f https://github.com/codam-coding-college/MLX42.git

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# Compile libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Make obj directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@rmdir $(OBJ_DIR) 2>/dev/null || true
	@make -C $(LIBFT_DIR) clean

# Clean object and executable filesdwa
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Clean and rebuild executable
re: fclean all

.PHONY: all clean fclean re bonus
