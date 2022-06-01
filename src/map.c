/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/01 20:08:53 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_height(t_vars *vars)
{
	int		fd;
	int		i;
	char	*line;

	i = 1;
	fd = open(vars->mapname, 0);
	line = get_next_line(fd);
	vars->map_x = ft_strlen_n(line) + 1;
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

char	**create_map(t_vars *vars)
{
	char	**map;
	int		fd;
	int		i;

	i = 0;
	vars->map_y = get_map_height(vars);
	fd = open(vars->mapname, 0);
	map = malloc(sizeof(char *) * vars->map_y);
	map[0] = get_next_line(fd);
	while (++i < vars->map_y)
		map[i] = get_next_line(fd);
	close(fd);
	return (map);
}

void	print_map(t_vars *v)
{
	int	x;
	int	y;

	y = -1;
	while (v->map[++y])
	{
		x = -1;
		while (v->map[y][++x])
		{
			if (v->map[y][x] == '1')
				print_wall(v, x, y);
			if (v->map[y][x] == '0')
				ft_put_win(v, x, y, v->sprites.f);
			if (v->map[y][x] == 'P')
				ft_put_win(v, x, y, v->sprites.p_u);
			if (v->map[y][x] == 'E')
				ft_put_win(v, x, y, v->sprites.e[0]);
			if (v->map[y][x] == 'C')
			{
				ft_put_win(v, x, y, v->sprites.c[0]);
				v->collec++;
			}
		}
	}
}
