/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/01 19:47:47 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	mlx_destroy_image(v->mlx, v->sprites.p_u);
	mlx_destroy_image(v->mlx, v->sprites.p_d);
	mlx_destroy_image(v->mlx, v->sprites.p_l);
	mlx_destroy_image(v->mlx, v->sprites.p_r);
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

int	move_player(int dy, int dx, void *psprite, t_vars *v)
{
	int	x;
	int	y;

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
				mlx_put_image_to_window(v->mlx, v->win, v->sprites.f,
					IMG_SIZE * x, IMG_SIZE * y);
				v->map[y + dy][x + dx] = 'P';
				mlx_put_image_to_window(v->mlx, v->win, psprite,
					IMG_SIZE * (x + dx), IMG_SIZE * (y + dy));
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
	mlx_put_image_to_window(v->mlx, v->win,
		v->sprites.w_d, IMG_SIZE, IMG_SIZE * (v->map_y - 2));
	mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_d,
		IMG_SIZE * 2, IMG_SIZE * (v->map_y - 2));
	mlx_string_put(v->mlx, v->win, IMG_SIZE + 5,
		(v->map_y - 1) * IMG_SIZE - 10, 0x44434d, "Moves:");
	mlx_string_put(v->mlx, v->win, IMG_SIZE + 45,
		(v->map_y - 1) * IMG_SIZE - 10, 0x44434d, str);
	free(str);
}

int	inputs(int key, t_vars *vars)
{
	if (key == ESC)
		exit_game(vars);
	else if (key == KEY_UP)
		move_player(1, 0, vars->sprites.p_u, vars);
	else if (key == KEY_LEFT)
		move_player(0, -1, vars->sprites.p_l, vars);
	else if (key == KEY_DOWN)
		move_player(-1, 0, vars->sprites.p_d, vars);
	else if (key == KEY_RIGHT)
		move_player(0, 1, vars->sprites.p_r, vars);
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
	vars.collec = 0;
	vars.moves = 0;
	vars.e_frm = 0;
	vars.c_frm = 0;
	vars.sprites = get_sprites(vars);
	vars.map = create_map(&vars);
	vars.win = mlx_new_window(vars.mlx, IMG_SIZE * vars.map_x,
			IMG_SIZE * (vars.map_y - 1), "Super Romil!");
	print_map(&vars);
	mlx_key_hook(vars.win, inputs, &vars);
	mlx_loop_hook(vars.mlx, frames, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop(vars.mlx);
}
