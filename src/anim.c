/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:56:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/01 19:33:27 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collec_animation(t_vars *vars)
{
	int			y;
	int			x;
	static int	i;

	if (i > COLLEC_FRAMES)
		i = 0;
	y = -1;
	while (vars->map[++y])
	{
		x = -1;
		while (vars->map[y][++x])
			if (vars->map[y][x] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->sprites.c[i], x * IMG_SIZE, y * IMG_SIZE);
	}
	i++;
}

int	frames(t_vars *vars)
{
	static int	i;

	i++;
	if (i / 4)
	{
		i = 0;
		collec_animation(vars);
		exit_animation(vars);
		enemies(vars);
	}
	usleep(1000000 / FPS);
	return (0);
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
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->sprites.e[i], x * IMG_SIZE, y * IMG_SIZE);
	}
	i++;
}
