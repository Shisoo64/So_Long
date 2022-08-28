/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:08:28 by rlaforge          #+#    #+#             */
/*   Updated: 2022/08/23 16:09:41 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map(char **map, t_vars *v)
{
	check_rectangle(map, v);
	check_borders(map, v);
	check_items(map, v);
	check_map_ext(v);
}

int	check_rectangle(char **map, t_vars *v)
{
	int		y;

	y = -1;
	while (map[++y])
		if (ft_strlen(map[y]) != ft_strlen(map[0]))
			return (ft_error(v, "Error\nMap is not a rectangle.\n"));
	return (0);
}

int	check_borders(char **map, t_vars *v)
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
				return (ft_error(v, "Error\nWrong map border.\n"));
			else if (y == v->map_y && map[y][x] != '1')
				return (ft_error(v, "Error\nWrong map border.\n"));
			else if (x == 0 && map[y][x] != '1')
				return (ft_error(v, "Error\nWrong map border.\n"));
			else if (x == v->map_x && map[y][x] != '1')
				return (ft_error(v, "Error\nWrong map border.\n"));
		}
	}
	return (0);
}

void	check_items(char **map, t_vars *v)
{
	int	x;
	int	y;
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] != '\n')
		{
			if (map[y][x] == 'E')
				i[0]++;
			else if (map[y][x] == 'P')
				i[1]++;
			else if (map[y][x] == 'C')
				i[2]++;
			else if (map[y][x] != '1' && map[y][x] != '0' \
			&& map[y][x] != 'M' && map[y][x] != 'X' && map[y][x] != 'C')
				ft_error(v, "Error\nWrong item on map.\n");
		}
	}
	if (i[0] != 1 || i[2] <= 0 || i[1] != 1)
		ft_error(v, "Error\nProblem with item numbers.\n");
}

int	ft_error(t_vars *v, char *str)
{
	ft_printf(str, "%s");
	exit_game_light(v, 1);
	return (1);
}
