# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgodecke <cgodecke@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 15:39:27 by cgodecke          #+#    #+#              #
#    Updated: 2023/10/03 15:47:04 by cgodecke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC_FLAGS = -Wall -Wextra -g -fsanitize=address #-Werror
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
					src/raycaster/render_image.c\
					src/raycaster/draw_line.c\
					src/raycaster/deg_to_rad.c\
					src/raycaster/ray_q1.c\
					src/raycaster/ray_q2.c\
					src/raycaster/ray_q3.c\
					src/raycaster/ray_q4.c\
					src/raycaster/unit_ray_x_length.c\
					src/raycaster/unit_ray_y_length.c\
					src/raycaster/draw_texture.c\
					src/raycaster/interface.c\
						src/mlx/handle_keypress.c\
						src/mlx/start_mlx.c\
						src/mlx/window_close.c\
						src/mlx/img_pix_put.c\

OBJFILES = $(INFILES:%.c=$(OBJDIR)/%.o)

NAME = cub3D

all: library setup $(NAME)

library:
	make -C includes/libft
	make -C includes/minilibx-linux

$(NAME): $(OBJFILES) ${HEADER}
	$(CC) $(CC_FLAGS) $(INFILES) -o $(NAME) includes/libft/libft.a includes/minilibx-linux/libmlx.a includes/minilibx-linux/libmlx_Linux.a -I/usr/X11/include -L/usr/X11/lib -lX11 -lXext -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@ -I/usr/X11/include

setup:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/src
	@mkdir -p $(OBJDIR)/src/parsing
	@mkdir -p $(OBJDIR)/src/raycaster
	@mkdir -p $(OBJDIR)/src/mlx

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
