/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:09:24 by rlaforge          #+#    #+#             */
/*   Updated: 2022/07/06 16:16:08 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	win_game(t_vars *v)
{
	v->game_end = 1;
	ft_put_win(v, v->map_x / 2, v->map_y / 2, v->sprites.win);
}

void	print_map_ext(t_vars *v, char c, int y, int x)
{
	if (c == 'X')
	{
		ft_put_win(v, x, y, v->sprites.x_l[0]);
		v->monsters_nbr++;
	}
	if (c == 'M')
	{
		ft_put_win(v, x, y, v->sprites.m_l[0]);
		v->mouses_nbr++;
	}
	if (c == 'C')
	{
		ft_put_win(v, x, y, v->sprites.c[0]);
		v->collec++;
	}
}

void	get_mouse_coord(t_vars *v)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = -1;
	v->m_coord[0] = (int *)malloc(sizeof(int) * v->mouses_nbr);
	v->m_coord[1] = (int *)malloc(sizeof(int) * v->mouses_nbr);
	while (v->map[++y])
	{
		x = -1;
		while (v->map[y][++x])
		{
			if (v->map[y][x] == 'M')
			{
				v->m_coord[0][i] = y;
				v->m_coord[1][i++] = x;
			}
		}
	}
}

void	get_enemy_coord(t_vars *v)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = -1;
	v->x_coord[0] = (int *)malloc(sizeof(int) * v->monsters_nbr);
	v->x_coord[1] = (int *)malloc(sizeof(int) * v->monsters_nbr);
	while (v->map[++y])
	{
		x = -1;
		while (v->map[y][++x])
		{
			if (v->map[y][x] == 'X')
			{
				v->x_coord[0][i] = y;
				v->x_coord[1][i++] = x;
			}
		}
	}
}
