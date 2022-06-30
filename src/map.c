/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/27 15:19:44 by rlaforge         ###   ########.fr       */
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

int	get_map_height(t_vars *vars)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(vars->mapname, 0);
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
	if (check_map(map, vars))
		return (map);
	exit(0);
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
				ft_put_win(v, x, y, v->sprites.p_r[0]);
			}
			if (v->map[y][x] == 'E')
				ft_put_win(v, x, y, v->sprites.e[0]);
			if (v->map[y][x] == 'X')
			{
				ft_put_win(v, x, y, v->sprites.x_l[0]);
				v->monsters_nbr++;
			}
			if (v->map[y][x] == 'M')
			{
				ft_put_win(v, x, y, v->sprites.m_l[0]);
				v->mouses_nbr++;
			}
			if (v->map[y][x] == 'C')
			{
				ft_put_win(v, x, y, v->sprites.c[0]);
				v->collec++;
			}
		}
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
