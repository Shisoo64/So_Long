/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:56:33 by rlaforge          #+#    #+#             */
/*   Updated: 2022/05/26 21:00:12 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_delay(int *timer, int delay)
{
	if (*timer <= delay)
	{
		*timer += 1;
		return (1);
	}
	*timer = 0;
	return (0);
}

void	collec_animation(t_vars *vars)
{
	int			y;
	int			x;
	static int	i;

	if (ft_delay(&vars->timer, 2500) == 1)
		return ;
	if (i >= COLLEC_FRAMES)
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
	collec_animation(vars);
	return (0);
}

void	check_collec(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (vars->map[++y] && vars->collec == 0)
	{
		x = -1;
		while (vars->map[y][++x])
			if (vars->map[y][x] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->sprites.e[1], x * IMG_SIZE, y * IMG_SIZE);
	}
}
