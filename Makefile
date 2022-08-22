# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/18 16:20:40 by rlaforge          #+#    #+#              #
#    Updated: 2022/07/08 17:04:39 by rlaforge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/main.c \
		src/utils.c \
		src/utils2.c \
		src/enemies.c \
		src/sprites.c \
		src/map.c \
		src/free.c \
		src/error.c \
		src/anim.c

CC = gcc -g

NAME = so_long

OBJS = $(SRCS:.c=.o)

CLIB = ar -rcs

GNL_DIR = ./src/get_next_line/

GNL = get_next_line.c \
	get_next_line_utils.c \

GNL_OBJS = ${addprefix ${GNL_DIR}, ${GNL:.c=.o}}

PRTF_DIR = ./src/ft_printf/

PRTF = ft_printf.c \
	ft_printf_utils.c \

PRTF_OBJS = ${addprefix ${PRTF_DIR}, ${PRTF:.c=.o}}

all : $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS) $(GNL_OBJS) $(PRTF_OBJS)
	$(CC) $(OBJS) $(GNL_OBJS) $(PRTF_OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	rm -f $(OBJS) $(GNL_OBJS) $(PRTF_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean
