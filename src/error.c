/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:08:28 by rlaforge          #+#    #+#             */
/*   Updated: 2022/07/06 16:08:29 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(char **map, t_vars *v)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] != '\n')
		{
			if (y == 0 && map[y][x] != '1')
				return (0);
			else if (y == v->map_y && map[y][x] != '1')
				return (0);
			else if (x == 0 && map[y][x] != '1')
				return (0);
			else if (x == v->map_x && map[y][x] != '1')
				return (0);
		}
	}
	return (1);
}
