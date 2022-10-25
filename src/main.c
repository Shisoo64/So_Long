/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/19 15:50:54 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_player(int dy, int dx, t_vars *v)
{
	int	x;
	int	y;

	x = v->p_x;
	y = v->p_y;
	if (v->map[y][x] == 'P' && (v->map[y + dy][x + dx] == '0' || \
		v->map[y + dy][x + dx] == 'C'))
	{
		if (v->map[y + dy][x + dx] == 'C')
			v->collec--;
		v->map[y][x] = '0';
		ft_put_win(v, x, y, v->sprites.f);
		ft_put_win(v, x + dx, y + dy, v->sprites.p);
		v->map[y + dy][x + dx] = 'P';
		v->p_x += dx;
		v->p_y += dy;
		return (1);
	}
	if (v->map[y][x] == 'P' && \
		v->map[y + dy][x + dx] == 'E' && v->collec == 0)
		exit_game(v);
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
	vars.collec = 0;
	vars.moves = 1;
	vars.sprites = get_sprites(vars);
	vars.map = create_map(&vars);
	check_map(vars.map, &vars);
	vars.win = mlx_new_window(vars.mlx, IMG_SIZE * (vars.map_x + 1),
			IMG_SIZE * (vars.map_y), "so_long");
	print_map(&vars);
	check_if_doable(&vars);
	mlx_key_hook(vars.win, inputs, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop(vars.mlx);
}
