# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 21:02:17 by cstoia            #+#    #+#              #
#    Updated: 2024/09/22 17:48:39 by cstoia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
GNL_DIR = get_next_line
LIBFT_DIR = libft
CC = CC
CFLAGS = -Wall -Wextra -Werror
INCLUDES = ./libft.h

GNL = \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c \
		$(GNL_DIR)/get_next_line.c

CFILES = \
		./ft_atoi.c \
		./ft_bzero.c \
		./ft_calloc.c \
		./ft_isalnum.c \
		./ft_isalpha.c \
		./ft_isascii.c \
		./ft_isdigit.c \
		./ft_isprint.c \
		./ft_memchr.c \
		./ft_memcmp.c \
		./ft_memcpy.c \
		./ft_memmove.c \
		./ft_memset.c \
		./ft_strchr.c \
		./ft_strdup.c \
		./ft_strlcat.c \
		./ft_strlcpy.c \
		./ft_strlen.c \
		./ft_strncmp.c \
		./ft_strnstr.c \
		./ft_strrchr.c \
		./ft_tolower.c \
		./ft_toupper.c \
		./ft_substr.c \
		./ft_strjoin.c \
		./ft_strtrim.c \
		./ft_split.c \
		./ft_itoa.c \
		./ft_strmapi.c\
		./ft_striteri.c \
		./ft_putchar_fd.c \
		./ft_putstr_fd.c \
		./ft_putendl_fd.c \
		./ft_putnbr_fd.c

OBJECTS = \
		$(CFILES:%.c=%.o) \
		$(GNL:$(GNL_DIR)/%.c=$(GNL_DIR)/%.o) \

CFILES_BONUS = \
		./ft_lstadd_back_bonus.c \
		./ft_lstadd_front_bonus.c \
		./ft_lstclear_bonus.c \
		./ft_lstdelone_bonus.c \
		./ft_lstiter_bonus.c \
		./ft_lstlast_bonus.c \
		./ft_lstmap_bonus.c \
		./ft_lstnew_bonus.c \
		./ft_lstsize_bonus.c

OBJECTS_BONUS = $(CFILES_BONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(INCLUDES)
		ar rcs $(NAME) $(OBJECTS)

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

bonus: $(OBJECTS) $(OBJECTS_BONUS)
			ar rcs $(NAME) $(OBJECTS) $(OBJECTS_BONUS)

.PHONY : all clean fclean re bonus
