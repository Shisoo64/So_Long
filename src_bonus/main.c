/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/14 19:53:06 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_player(int dy, int dx, t_vars *v)
{
	int	x;
	int	y;

	if (dx != 0)
		v->p_dir = dx;
	x = v->p_x;
	y = v->p_y;
	if (v->map[y][x] == 'P' && (v->map[y + dy][x + dx] == '0' || \
		v->map[y + dy][x + dx] == 'C'))
	{
		if (v->map[y + dy][x + dx] == 'C')
			v->collec--;
		v->map[y][x] = '0';
		ft_put_win(v, x, y, v->sprites.f);
		v->map[y + dy][x + dx] = 'P';
		v->p_x += dx;
		v->p_y += dy;
		return (1);
	}
	if (v->map[y][x] == 'P' && \
		v->map[y + dy][x + dx] == 'E' && v->collec == 0)
		win_game(v);
	return (0);
}

int	frames(t_vars *vars)
{
	static int	i;

	if (vars->game_end == 1)
		return (0);
	if (i++ / 4)
	{
		i = 0;
		collec_animation(vars);
		exit_animation(vars);
	}
	if (i / 2 && vars->monsters_nbr != 0 && vars->mouses_nbr != 0)
	{
		mouses(vars);
		monsters(vars);
	}
	player_animation(vars);
	usleep(1000000 / FPS);
	return (0);
}

int	inputs(int key, t_vars *vars)
{
	if (key == ESC)
		exit_game(vars);
	else if (vars->game_end == 1)
		return (0);
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

int	exit_hook(t_vars *vars)
{
	exit_game(vars);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (1);
	vars.mapname = av[1];
	vars.mlx = mlx_init();
	vars.game_end = 0;
	vars.p_dir = 1;
	vars.collec = 0;
	vars.mouses_nbr = 0;
	vars.monsters_nbr = 0;
	vars.moves = 1;
	vars.sprites = get_sprites(vars);
	vars.map = create_map(&vars);
	check_map(vars.map, &vars);
	vars.win = mlx_new_window(vars.mlx, IMG_SIZE * (vars.map_x + 1),
			IMG_SIZE * (vars.map_y), "So_long Romil!");
	print_map(&vars);
	get_mouse_coord(&vars);
	get_enemy_coord(&vars);
	printf("1printf: %d\n", vars.p_x);
	ft_printf("1 p_y [%d]\n", vars.p_y);
	check_if_doable(&vars);
	mlx_key_hook(vars.win, inputs, &vars);
	mlx_loop_hook(vars.mlx, frames, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop(vars.mlx);
}
