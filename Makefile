# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 13:37:33 by ecamara           #+#    #+#              #
#    Updated: 2022/12/16 13:45:15 by ecamara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = sim

SRC =	src/main.c	\
		src/math/col_math.c			\
		src/math/couple_math1.c		\
		src/math/couple_math2.c		\
		src/math/couple_math3.c		\
		src/math/couple.c			\
		src/math/math.c				\
		src/math/matrix_math.c		\
		src/math/matrix_set.c		\
		src/math/uv.c				\
		src/node.c				\
		src/bootup.c			\
		src/keyWords.c			\
		src/terminalFuncts.c	\
		src/input.c				\
		src/aux.c				\
		src/simulation.c		\
		src/cubism.c			\
		src/render.c			\
		src/config.c			\

INCLUDES = minirt.h

SRCO = $(SRC:.c=.o)

FLG = -Wall -Werror -Wextra -O2 #-g3 -fsanitize=address 
RLFLG = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib/
CPPFLAGS= -I/Users/$(USER)/.brew/opt/readline/include
CC = gcc

LIB = libft/libft.a
MLX = mlx/libmlx.a

all: $(NAME)
bonus: $(NAME)

%.o: %.c
	$(CC) $(FLG) -c $^ -o $@

$(NAME): $(SRCO) $(LIB) $(MLX)
	$(CC) $(FLG) $(RLFLG) $(CPPFLAGS) -framework OpenGL -framework AppKit $^ -o $@

$(LIB):
	make -C libft

$(MLX) :
	make -C mlx

clean:
	make -C libft/ clean
	make -C mlx/ clean
	rm -f $(SRCO)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

re_bonus: fclean

.PHONY: all clean fclean re 
