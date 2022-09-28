/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2022/08/24 15:27:51 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_height(t_vars *vars)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(vars->mapname, 0);
	if (fd == -1)
	{
		ft_printf("Error\nProblem with mapname", "%s");
		exit_game_light(vars, 0);
		return (0);
	}
	line = get_next_line(fd);
	vars->map_x = ft_strlen_n(line);
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

	i = -1;
	vars->map_y = get_map_height(vars);
	fd = open(vars->mapname, 0);
	map = malloc(sizeof(char *) * (vars->map_y + 1));
	while (++i < vars->map_y)
		map[i] = get_next_line(fd);
	map[vars->map_y] = NULL;
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
			{
				v->p_x = x;
				v->p_y = y;
				ft_put_win(v, x, y, v->sprites.p);
			}
			print_map_ext(v, v->map[y][x], y, x);
		}
	}
}

void	print_map_ext(t_vars *v, char c, int y, int x)
{
	if (v->map[y][x] == 'E')
		ft_put_win(v, x, y, v->sprites.e);
	if (c == 'C')
	{
		ft_put_win(v, x, y, v->sprites.c);
		v->collec++;
	}
}
