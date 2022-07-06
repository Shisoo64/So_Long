/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:53:58 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/28 19:53:59 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	monsters(t_vars *vars)
{
	static int	i;
	static int	x;
	int			dir;

	if (x > ENEMY_FRAMES)
		x = 0;
	if (++i >= vars->monsters_nbr)
		i = 0;
	dir = rand() % 4;
	if (dir == 0)
		move_enemy(vars, (int []){-1, 0}, i, vars->sprites.x_l[x]);
	if (dir == 1)
		move_enemy(vars, (int []){1, 0}, i, vars->sprites.x_r[x]);
	if (dir == 2)
		move_enemy(vars, (int []){0, -1}, i, vars->sprites.x_l[x]);
	if (dir == 3)
		move_enemy(vars, (int []){0, 1}, i, vars->sprites.x_r[x]);
}

void	move_enemy(t_vars *v, int d[2], int i, void *sprite)
{
	int	x;
	int	y;

	y = v->x_coord[0][i];
	x = v->x_coord[1][i];
	if (v->map[y][x] == 'X')
	{
		if (v->map[y + d[0]][x + d[1]] == 'P')
			exit_game(v);
		if (v->map[y + d[0]][x + d[1]] == '0')
		{	
			v->map[y][x] = '0';
			ft_put_win(v, x, y, v->sprites.f);
			v->map[y + d[0]][x + d[1]] = 'X';
			ft_put_win(v, x + d[1], y + d[0], sprite);
			v->x_coord[0][i] += d[0];
			v->x_coord[1][i] += d[1];
		}
	}
}

void	mouses(t_vars *vars)
{
	static int	i;
	static int	m;
	int			dir;

	if (m > ENEMY_FRAMES)
		m = 0;
	if (++i >= vars->mouses_nbr)
		i = 0;
	dir = rand() % 4;
	if (dir == 0)
		move_mouse(vars, (int []){-1, 0}, i, vars->sprites.m_l[m]);
	if (dir == 1)
		move_mouse(vars, (int []){1, 0}, i, vars->sprites.m_r[m]);
	if (dir == 2)
		move_mouse(vars, (int []){0, -1}, i, vars->sprites.m_l[m]);
	if (dir == 3)
		move_mouse(vars, (int []){0, 1}, i, vars->sprites.m_r[m]);
}

void	move_mouse(t_vars *v, int d[2], int i, void *sprite)
{
	int	x;
	int	y;

	y = v->m_coord[0][i];
	x = v->m_coord[1][i];
	if (v->map[y][x] == 'M' && v->map[y + d[0]][x + d[1]] == '0')
	{	
		v->map[y][x] = '0';
		ft_put_win(v, x, y, v->sprites.f);
		v->map[y + d[0]][x + d[1]] = 'M';
		ft_put_win(v, x + d[1], y + d[0], sprite);
		v->m_coord[0][i] += d[0];
		v->m_coord[1][i] += d[1];
	}
}
