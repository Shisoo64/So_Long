/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:09:24 by rlaforge          #+#    #+#             */
/*   Updated: 2022/08/22 19:04:21 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	win_game(t_vars *v)
{
	v->game_end = 1;
	mlx_put_image_to_window(v->mlx, v->win, v->sprites.win, \
	v->map_x * 16 - 145, v->map_y * 16 - 33);
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
