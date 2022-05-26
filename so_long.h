/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2022/05/26 21:02:51 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include "./get_next_line/get_next_line.h"

# define IMG_SIZE 32
# define COLLEC_FRAMES 3

typedef struct	s_sprites {
	void	*f;
	void	*c[COLLEC_FRAMES + 1];
	void	*p_u;
	void	*p_d;
	void	*p_l;
	void	*p_r;
	void	*e[2];
	void	*w;
	void	*w_d;
	void	*w_dl;
	void	*w_dr;
	void	*w_l;
	void	*w_r;
	void	*w_ul;
	void	*w_ur;
	void	*w_u;

}				t_sprites;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	char	**map;
	char	*mapname;
	int	map_y;
	int	map_x;
	int	collec;
	int	moves;
	int	timer;
	t_sprites	sprites;
}				t_vars;

enum e_keycode
{
	KEY_UP = 115,
	KEY_DOWN = 119,
	KEY_LEFT = 97,
	KEY_RIGHT = 100,
	ESC = 0xFF1B
};

int ft_strlen_n(const char *s);
void	print_wall(t_vars *v, int x, int y);
void	print_map(t_vars *vars);
char	**create_map(t_vars *vars);
int	get_map_height(t_vars *vars);
t_sprites	get_sprites(t_vars v);
char	*ft_itoa(int n);
int	ft_delay(int *timer, int delay);
void    collec_animation(t_vars *vars);
int frames(t_vars *vars);
void    check_collec(t_vars *vars);

#endif
