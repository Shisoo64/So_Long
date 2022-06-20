/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/20 15:11:02 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	monsters(t_vars *vars)
{
	static int	i;
	int		dir;

	if (i++ > vars->monsters_nbr)
		i = 0;
	dir = rand() % 4;
	if (dir == 0)
		move_enemy(vars, (int []){-1, 0}, vars->sprites.x_l[xsprite_i()], i, 'X');
	if (dir == 1)
		move_enemy(vars, (int []){1, 0}, vars->sprites.x_r[xsprite_i()], i, 'X');
	if (dir == 2)
		move_enemy(vars, (int []){0, -1}, vars->sprites.x_l[xsprite_i()], i, 'X');
	if (dir == 3)
		move_enemy(vars, (int []){0, 1}, vars->sprites.x_r[xsprite_i()], i, 'X');
}

void	mouses(t_vars *vars)
{
	static int	i;
	int		dir;

	if (i++ > vars->mouses_nbr)
		i = 0;
	dir = rand() % 4;
	if (dir == 0)
		move_enemy(vars, (int []){-1, 0}, vars->sprites.m_l[msprite_i()], i, 'M');
	if (dir == 1)
		move_enemy(vars, (int []){1, 0}, vars->sprites.m_r[msprite_i()], i, 'M');
	if (dir == 2)
		move_enemy(vars, (int []){0, -1}, vars->sprites.m_l[msprite_i()], i, 'M');
	if (dir == 3)
		move_enemy(vars, (int []){0, 1}, vars->sprites.m_r[msprite_i()], i, 'M');
}

void	move_enemy(t_vars *v, int d[2], void *sprite, int nbr, char c)
{
	int	x;
	int	y;
	int	i;

	y = -1;
	i = 0;
	while (v->map[++y])
	{
		x = -1;
		while (v->map[y][++x])
		{
			if (v->map[y][x] == c)
			{
				if (i == nbr && c == 'X' && v->map[y + d[0]][x + d[1]] == 'P')
					exit_game(v);
				if (i++ == nbr && v->map[y + d[0]][x + d[1]] == '0')
				{	
					v->map[y][x] = '0';
					ft_put_win(v, x, y, v->sprites.f);
					v->map[y + d[0]][x + d[1]] = c;
					ft_put_win(v, x + d[1], y + d[0], sprite);
					return ;
				}
			}
		}
	}
}

void	free_map(t_vars *vars)
{
	int	y;

	y = 0;
	while (y < vars->map_y)
		free(vars->map[y++]);
	free(vars->map);
}

void	free_img(t_vars *v)
{
	mlx_destroy_image(v->mlx, v->sprites.f);
	mlx_destroy_image(v->mlx, v->sprites.c[0]);
	mlx_destroy_image(v->mlx, v->sprites.c[1]);
	mlx_destroy_image(v->mlx, v->sprites.c[2]);
	mlx_destroy_image(v->mlx, v->sprites.c[3]);
	mlx_destroy_image(v->mlx, v->sprites.p_l[0]);
	mlx_destroy_image(v->mlx, v->sprites.p_l[1]);
	mlx_destroy_image(v->mlx, v->sprites.p_l[2]);
	mlx_destroy_image(v->mlx, v->sprites.p_l[3]);
	mlx_destroy_image(v->mlx, v->sprites.p_r[0]);
	mlx_destroy_image(v->mlx, v->sprites.p_r[1]);
	mlx_destroy_image(v->mlx, v->sprites.p_r[2]);
	mlx_destroy_image(v->mlx, v->sprites.p_r[3]);
	mlx_destroy_image(v->mlx, v->sprites.e[0]);
	mlx_destroy_image(v->mlx, v->sprites.e[1]);
	mlx_destroy_image(v->mlx, v->sprites.e[2]);
	mlx_destroy_image(v->mlx, v->sprites.w);
	mlx_destroy_image(v->mlx, v->sprites.w_u);
	mlx_destroy_image(v->mlx, v->sprites.w_ul);
	mlx_destroy_image(v->mlx, v->sprites.w_ur);
	mlx_destroy_image(v->mlx, v->sprites.w_l);
	mlx_destroy_image(v->mlx, v->sprites.w_r);
	mlx_destroy_image(v->mlx, v->sprites.w_d);
	mlx_destroy_image(v->mlx, v->sprites.w_dl);
	mlx_destroy_image(v->mlx, v->sprites.w_dr);
}

void	exit_game(t_vars *vars)
{
	free_map(vars);
	free_img(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

static int	exit_hook(t_vars *vars)
{
	exit_game(vars);
	return (0);
}

int	move_player(int dy, int dx, t_vars *v)
{
	int	x;
	int	y;

	if (dx != 0)
		v->p_dir = dx;
	y = -1;
	while (v->map[++y])
	{
		x = -1;
		while (v->map[y][++x])
		{
			if (v->map[y][x] == 'P' && (v->map[y + dy][x + dx] == '0' || \
				v->map[y + dy][x + dx] == 'C'))
			{
				if (v->map[y + dy][x + dx] == 'C')
					v->collec--;
				v->map[y][x] = '0';
				ft_put_win(v, x, y, v->sprites.f);
				v->map[y + dy][x + dx] = 'P';
				return (1);
			}
			if (v->map[y][x] == 'P' && \
				v->map[y + dy][x + dx] == 'E' && v->collec == 0)
				exit_game(v);
		}
	}
	return (0);
}

void	display_moves(t_vars *v)
{
	char	*str;

	str = ft_itoa(v->moves++);
	ft_put_win(v, 1, v->map_y - 1, v->sprites.w_d);
	ft_put_win(v, 2, v->map_y - 1, v->sprites.w_d);
	mlx_string_put(v->mlx, v->win, IMG_SIZE + 5,
		(v->map_y) * IMG_SIZE - 10, 0xffffff, "Moves:");
	mlx_string_put(v->mlx, v->win, IMG_SIZE + 45,
		(v->map_y) * IMG_SIZE - 10, 0xffffff, str);
	free(str);
}

int	frames(t_vars *vars)
{
	static int	i;

	if (i++ / 4)
	{
		i = 0;
		collec_animation(vars);
		exit_animation(vars);
	}
	if (i / 2)
		mouses(vars);
	monsters(vars);
	player_animation(vars);
	usleep(1000000 / FPS);
	return (0);
}

int	inputs(int key, t_vars *vars)
{
	if (key == ESC)
		exit_game(vars);
	else if (key == KEY_UP)
		move_player(1, 0, vars);
	else if (key == KEY_LEFT)
		move_player(0, -1, vars);
	else if (key == KEY_DOWN)
		move_player(-1, 0, vars);
	else if (key == KEY_RIGHT)
		move_player(0, 1, vars);
	else
		return (0);
	display_moves(vars);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (1);
	vars.mapname = av[1];
	vars.mlx = mlx_init();
	vars.p_dir = 1;
	vars.collec = 0;
	vars.mouses_nbr = 0;
	vars.monsters_nbr = 0;
	vars.moves = 1;
	vars.sprites = get_sprites(vars);
	vars.map = create_map(&vars);
	vars.win = mlx_new_window(vars.mlx, IMG_SIZE * (vars.map_x + 1),
			IMG_SIZE * (vars.map_y), "So_long Romil!");
	print_map(&vars);
	mlx_key_hook(vars.win, inputs, &vars);
	mlx_loop_hook(vars.mlx, frames, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop(vars.mlx);
}
