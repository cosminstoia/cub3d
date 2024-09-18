# Program name
NAME		= cub3D

# Compiler
CC			= cc

# Compilation flags
CFLAGS		= -Wall -Wextra -Werror -Wunreachable-code -Ofast

# Include libraries and header files
LIBMLX	= ./MLX42
HEADERS	= -I ./includes -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Directories
SRC_DIR		= src
OBJ_DIR		= obj

# Source files
SRCS		=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/draw_minimap.c \
				$(SRC_DIR)/move_player.c

# Objects
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: libmlx $(NAME)

libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Build project
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(NAME) built successfully"

# add libmlx
$(LIBMLX):
	@touch .gitmodules
	@git submodule add -f https://github.com/codam-coding-college/MLX42.git

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# Make obj directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	@rm -f $(OBJS)
	@rm -rf $(LIBMLX)/build
	@rmdir $(OBJ_DIR) 2>/dev/null || true

# Clean object and executable files
fclean: clean
	@rm -f $(NAME)

# Clean and rebuild executable
re: fclean all

.PHONY: all clean fclean re bonus
