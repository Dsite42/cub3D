# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 15:39:27 by cgodecke          #+#    #+#              #
#    Updated: 2023/09/15 14:21:01 by ankinzin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC_FLAGS = -Wall -Wextra -g -fsanitize=address
OBJDIR = obj
HEADER := includes/cub3D.h
LIBFTDIR := includes/libft
LIBFT := libft.a
INFILES = 	src/main.c \
			src/free.c \
			src/general.c \
			src/general1.c \
			src/init_1.c \
			src/init_2.c \
			src/map_file.c \
			src/validate_element.c \
			src/validate_image.c \
			src/validate_map.c \
			src/validation.c \

OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

NAME = cub3D

all: library setup $(NAME)

library:
	make -C includes/libft
	make -C src/minilibx-linux

$(NAME): $(OBJFILES) ${HEADER}
	$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) includes/libft/libft.a src/minilibx-linux/libmlx.a src/minilibx-linux/libmlx_Darwin.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -I/usr/X11/include

setup:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/src

clean:
	make clean -C includes/libft
	make clean -C src/minilibx-linux
	rm -f $(OBJFILES)
	rm -r -f obj/

fclean: clean
	make fclean -C includes/libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean setup re
