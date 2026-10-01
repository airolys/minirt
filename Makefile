# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkermia <dkermia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/12 14:06:51 by dkermia           #+#    #+#              #
#    Updated: 2023/12/12 15:57:29 by dkermia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Put minilibx-linux folder in src folder

NAME	=	miniRT

CC	=	cc

CFLAGS	=	-Wall -Werror -Wextra -g3

RM	=	rm -f

SRC = src/main.c \
			src/init.c \
			src/hooks.c \
			src/parsing/parsing.c \
			src/parsing/alloc.c \
			src/parsing/get_next_line.c \
			src/parsing/objects/ambiant_lignt.c \
			src/parsing/objects/camera.c \
			src/parsing/objects/cylinder.c \
			src/parsing/objects/plane.c \
			src/parsing/objects/sphere.c \
			src/parsing/values/numbers.c \
			src/parsing/values/vectors.c \
			src/render/mlx.c \
			src/memory/memory_1.c \
			src/memory/memory_2.c \
			src/memory/memory_3.c \
			src/memory/memory_4.c \
			src/vector.c \
			src/vector2.c \
			src/matrix.c \
			src/matrix2.c \
			src/logic.c \
			src/compute/color.c \
			src/compute/camera.c \
			src/compute/plane.c \
			src/compute/sphere.c \
			src/compute/disc.c \
			src/compute/cylinder.c

HEADER	= includes/miniRT.h

OBJ = $(SRC:.c=.o)

DEP = $(SRC:.c=.d)

MLXFLAGS = minilibx-linux/libmlx.a -Lminilibx-linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz

all : $(NAME)

$(NAME): $(OBJ)
	$(info Compiling object files.)
	make -C minilibx-linux
	$(CC) $(OBJ) $(MLXFLAGS) -o $(NAME)
	$(info Compiling done.)

%.o: %.c $(HEADER)
	$(info Compiling source files.)
	@$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@
	$(info Compiling done.)
clean:
	$(info Cleaning object files.)
	$(RM) $(OBJ)
	$(RM) $(DEP)
	$(RM) $(NAME)
	make clean -C minilibx-linux
	$(info Cleaning done.)

fclean: clean
	$(RM) miniRT

re: fclean all

.SILENT:all $(NAME) clean fclean re