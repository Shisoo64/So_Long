# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 16:20:40 by rlaforge          #+#    #+#              #
#    Updated: 2022/08/24 15:41:58 by rlaforge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/main.c \
		src/utils.c \
		src/sprites.c \
		src/map.c \
		src/free.c \
		src/error.c

SRCS_BONUS =	src_bonus/main.c \
				src_bonus/utils.c \
				src_bonus/utils2.c \
				src_bonus/enemies.c \
				src_bonus/sprites.c \
				src_bonus/map.c \
				src_bonus/free.c \
				src_bonus/error.c \
				src_bonus/anim.c

CC = gcc

LIBFT = libft/libft.a

MLX = mlx_linux/libmlx.a

CFLAGS = -Wall -Wextra -Werror -g

NAME = so_long

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME)
	
$(LIBFT) :
	make -C libft/

$(MLX) :
	make -C mlx_linux/

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -o $(NAME)

bonus : $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -o $(NAME)

clean :
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	make -C libft/ fclean
	make -C mlx_linux/ clean

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean