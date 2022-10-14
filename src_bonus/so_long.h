/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/14 18:29:56 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

# define IMG_SIZE 32
# define FPS 30
# define PLAYER_FRAMES 3
# define ENEMY_FRAMES 3
# define COLLEC_FRAMES 3
# define EXIT_FRAMES 2 

typedef struct s_node
{
	struct s_node	*prev;
	int				y;
	int				x;
}				t_node;

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
	void	*win;
	void	*w[3];
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
	void		*mlx;
	void		*win;
	char		**map;
	char		*mapname;
	int			map_y;
	int			map_x;
	int			collec;
	int			mouses_nbr;
	int			*m_coord[2];
	int			*x_coord[2];
	int			monsters_nbr;
	int			moves;
	int			p_dir;
	int			p_x;
	int			p_y;
	int			vx;
	int			vy;
	int			game_end;
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

void		free_img(t_vars *v);
void		free_enemies(t_vars *v);
void		exit_game(t_vars *vars);
void		exit_game_light(t_vars *vars, int map);
int			ft_strlen_n(const char *s);
void		print_wall(t_vars *v, int x, int y);
void		print_map(t_vars *vars);
char		**create_map(t_vars *vars);
int			get_map_height(t_vars *vars);
t_sprites	get_sprites(t_vars v);
int			ft_delay(int *timer, int delay);
int			psprite_i(void);
void		player_animation(t_vars *vars);
void		collec_animation(t_vars *vars);
void		exit_animation(t_vars *vars);
int			frames(t_vars *vars);
void		ft_put_win(t_vars *v, int x, int y, void *sprite);
void		monsters(t_vars *vars);
void		mouses(t_vars *vars);
void		move_enemy(t_vars *v, int d[2], int i, void *sprite);
void		move_mouse(t_vars *v, int d[2], int i, void *sprite);
void		get_mouse_coord(t_vars *v);
void		get_enemy_coord(t_vars *v);
void		display_moves(t_vars *v);
void		print_map_ext(t_vars *v, char c, int y, int x);
void		win_game(t_vars *v);
void		check_map(char **map, t_vars *v);
void		free_map(t_vars *vars, char **map);
int			ft_error(t_vars *v, char *str);
void		check_items(char **map, t_vars *v);
int			check_borders(char **map, t_vars *v);
int			check_rectangle(char **map, t_vars *v);
void		check_map_ext(t_vars *v);
int			ft_printf(const char *str, ...);
void		check_if_doable(t_vars *v);

#endif
