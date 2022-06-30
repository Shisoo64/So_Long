/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:56:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/27 15:25:43 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	msprite_i(void)
{
	static int	i;

	if (i > ENEMY_FRAMES)
		i = 0;
	return (i++);
}

int	xsprite_i(void)
{
	static int	i;

	if (i > ENEMY_FRAMES)
		i = 0;
	return (i++);
}

int	psprite_i(void)
{
	static int	i;

	if (i > PLAYER_FRAMES * 8)
		i = 0;
	return (i++ / 8);
}

void	player_animation(t_vars *vars)
{
	int	y;
	int	x;

	y = -1;
	while (vars->map[++y])
	{
		x = -1;
		while (vars->map[y][++x])
		{
			if (vars->map[y][x] == 'P' && vars->p_dir == -1)
				ft_put_win(vars, x, y, vars->sprites.p_l[psprite_i()]);
			else if (vars->map[y][x] == 'P' && vars->p_dir == 1)
				ft_put_win(vars, x, y, vars->sprites.p_r[psprite_i()]);
		}
	}
}

void	collec_animation(t_vars *vars)
{
	int			y;
	int			x;
	static int	i;

	if (++i > COLLEC_FRAMES)
		i = 0;
	y = -1;
	while (vars->map[++y])
	{
		x = -1;
		while (vars->map[y][++x])
			if (vars->map[y][x] == 'C')
				ft_put_win(vars, x, y, vars->sprites.c[i]);
	}
}

void	exit_animation(t_vars *vars)
{
	int			x;
	int			y;
	static int	i;

	if (vars->collec != 0 || i > EXIT_FRAMES)
		return ;
	y = -1;
	while (vars->map[++y])
	{
		x = -1;
		while (vars->map[y][++x])
			if (vars->map[y][x] == 'E')
				ft_put_win(vars, x, y, vars->sprites.e[i++]);
	}
}
