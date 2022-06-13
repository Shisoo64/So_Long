/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/09 15:37:15 by rlaforge         ###   ########.fr       */
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
# define FPS 30
# define PLAYER_FRAMES 3
# define ENEMY_FRAMES 3
# define COLLEC_FRAMES 3
# define EXIT_FRAMES 2 

typedef struct s_sprites {
	void	*p_l[PLAYER_FRAMES + 1];
	void	*p_r[PLAYER_FRAMES + 1];
	void	*x_l[ENEMY_FRAMES + 1];
	void	*x_r[ENEMY_FRAMES + 1];
	void	*m_l[ENEMY_FRAMES + 1];
	void	*m_r[ENEMY_FRAMES + 1];
	void	*c[COLLEC_FRAMES + 1];
	void	*e[EXIT_FRAMES + 1];
	void	*f;
	void	*w;
	void	*w_d;
	void	*w_dl;
	void	*w_dr;
	void	*w_u;
	void	*w_ul;
	void	*w_ur;
	void	*w_l;
	void	*w_r;

}				t_sprites;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	char	**map;
	char	*mapname;
	int	map_y;
	int	map_x;
	int	collec;
	int	mouses_nbr;
	int	monsters_nbr;
	int	moves;
	int	p_dir;
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

void    free_map(t_vars *vars);
void    free_img(t_vars *v);
void    exit_game(t_vars *vars);
int ft_strlen_n(const char *s);
void	print_wall(t_vars *v, int x, int y);
void	print_map(t_vars *vars);
char	**create_map(t_vars *vars);
int	get_map_height(t_vars *vars);
t_sprites	get_sprites(t_vars v);
char	*ft_itoa(int n);
int	ft_delay(int *timer, int delay);
int psprite_i();
int xsprite_i();
int msprite_i();
void    player_animation(t_vars *vars);
void    collec_animation(t_vars *vars);
void    exit_animation(t_vars *vars);
int frames(t_vars *vars);
void ft_put_win(t_vars *v, int x, int y, void *sprite);
void    monsters(t_vars *vars);
void    mouses(t_vars *vars);
void    move_enemy(t_vars *v, int d[2], void *sprite, int nbr, char c);

#endif
