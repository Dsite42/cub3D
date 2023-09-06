# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 15:39:27 by cgodecke          #+#    #+#              #
#    Updated: 2023/09/06 09:27:43 by cgodecke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC_FLAGS = -Wall -Wextra  #-fsanitize=address -g3 #-Werror
OBJDIR = obj
HEADER := src/cub3D.h
LIBFTDIR := src/libft
LIBFT := libft.a
INFILES = 	src/main.c\
				src/raycaster/render_image.c\
				src/raycaster/draw_line.c\
				src/raycaster/deg_to_rad.c\
				src/raycaster/sky.c\
				src/raycaster/ray_q1.c\
				src/raycaster/ray_q2.c\
				src/raycaster/ray_q3.c\
				src/raycaster/ray_q4.c\
				src/raycaster/unit_ray_x_length.c\
				src/raycaster/unit_ray_y_length.c\
				src/raycaster/draw_texture.c\
					src/mlx/handle_keypress.c\
					src/mlx/start_mlx.c\
					src/mlx/window_close.c\
					src/mlx/img_pix_put.c\

OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

NAME = cub3D

all: library setup $(NAME)

library:
	make -C src/libft
	make -C src/minilibx-linux

$(NAME): $(OBJFILES) ${HEADER}
	$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) src/libft/libft.a src/minilibx-linux/libmlx.a src/minilibx-linux/libmlx_Linux.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -I/usr/X11/include

setup:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/src
	@mkdir -p $(OBJDIR)/src/raycaster
	@mkdir -p $(OBJDIR)/src/mlx

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