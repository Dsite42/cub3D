# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 15:39:27 by cgodecke          #+#    #+#              #
#    Updated: 2023/09/12 12:45:58 by ankinzin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC_FLAGS = -Wall -Wextra -Werror -fsanitize=address
OBJDIR = obj
HEADER := src/cub3D.h
LIBFTDIR := src/libft
LIBFT := libft.a
INFILES = 	src/main.c free.c general.c general1.c init_1.c init_2.c map_file.c\
				validate_element.c validate_image.c validate_map.c validation.c \

OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

NAME = cub3D

all: library setup $(NAME)

library:
	make -C src/libft
	make -C src/minilibx-linux

$(NAME): $(OBJFILES) ${HEADER}
	$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) src/libft/libft.a
# src/minilibx-linux/libmlx.a src/minilibx-linux/libmlx_Darwin.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@
#-I/usr/X11/include

setup:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/src

clean:
	make clean -C src/libft
	make clean -C src/minilibx-linux
	rm -f $(OBJFILES)
	rm -r -f obj/

fclean: clean
	make fclean -C src/libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean setup re
