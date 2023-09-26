# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 15:39:27 by cgodecke          #+#    #+#              #
#    Updated: 2023/09/26 09:15:43 by cgodecke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC_FLAGS = -Wall -Wextra -g -fsanitize=address
OBJDIR = obj
HEADER := includes/cub3D.h
LIBFTDIR := includes/libft
LIBFT := libft.a
INFILES = 	src/main.c \
			src/parsing/free.c \
			src/parsing/general.c \
			src/parsing/general1.c \
			src/parsing/init_1.c \
			src/parsing/map_file.c \
			src/parsing/validate_element.c \
			src/parsing/validate_image.c \
			src/parsing/validate_map.c \
			src/parsing/validation.c \

OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

NAME = cub3D

all: library setup $(NAME)

library:
	make -C includes/libft
	make -C includes/minilibx-linux

$(NAME): $(OBJFILES) ${HEADER}
	$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) includes/libft/libft.a includes/minilibx-linux/libmlx.a includes/minilibx-linux/libmlx_Darwin.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -I/usr/X11/include

setup:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/src
	@mkdir -p $(OBJDIR)/src/parsing


clean:
	make clean -C includes/libft
	make clean -C includes/minilibx-linux
	rm -f $(OBJFILES)
	rm -r -f obj/

fclean: clean
	make fclean -C includes/libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean setup re
