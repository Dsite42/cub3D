# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 15:39:27 by cgodecke          #+#    #+#              #
#    Updated: 2023/08/15 09:09:00 by cgodecke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC_FLAGS = -Wall -Wextra #-Werror
OBJDIR = obj
HEADER := cub3D.h
LIBFTDIR := libft
LIBFT := libft.a
INFILES = 	main.c\

OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

NAME = cub3D

all: library setup $(NAME)

library:
	make -C libft
	make -C minilibx-linux

$(NAME): $(OBJFILES) ${HEADER}
	$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Darwin.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm
#$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) libft/libft.a minilibx-linux/libmlx.a minilibx-linux/libmlx_Linux.a -I/usr/include/X11 -L/usr/lib/X11 -lX11 -lXext -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -I/usr/X11/include

setup:
	@mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJFILES) $(BONUSOBJFILES)
	rm -r -f obj/
	make clean -C libft 
	make clean -C minilibx-linux

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean setup re