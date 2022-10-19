# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 16:20:40 by rlaforge          #+#    #+#              #
#    Updated: 2022/10/19 18:13:43 by rlaforge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/main.c \
		src/pathfinding.c \
		src/utils.c \
		src/sprites.c \
		src/map.c \
		src/free.c \
		src/error.c

SRCS_BONUS =	src_bonus/main.c \
				src_bonus/pathfinding.c \
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

CFLAGS = -Wall -Wextra -Werror -g3

NAME = so_long

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME)


$(LIBFT) :
	make -C libft/

$(MLX) :
	make -C mlx_linux/

$(NAME): echo $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -o $(NAME)
	@echo "\033[1;32m📦 Program compiled!\033[0m"

echo :
	@echo "\e[5m🗜️  Program compiling...\033[0m"

bonus : $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(LIBFT) $(MLX) -lXext -lX11 -o $(NAME)

clean :
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	make -C libft/ fclean
	make -C mlx_linux/ clean
	@echo "\033[92m🧹 Program cleaned!\033[0m"

fclean : clean
	rm -rf $(NAME)
	@echo "\033[92mAnd executable too!\033[0m"

re : fclean all

.PHONY : all re clean fclean
.SILENT :