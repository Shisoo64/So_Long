/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:53:21 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/04 19:49:10 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	newnode(t_node **head, int y, int x)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node)
	{
		node->y = y;
		node->x = x;
		node->prev = NULL;
	}
	if (!*head || !head)
	{
		*head = node;
		return ;
	}
	node->prev = *head;
	*head = node;
}

void	check_if_doable(t_vars *v)
{
	t_node	*move;
	t_node	*tmp;
	char **map;
	int	x;
	int	y;
	int c;
	int	e;

	map = create_map(v);
	move = NULL;
	c = v->collec;
	e = 0;
	x = v->p_x;
	y = v->p_y;
	newnode(&move, y, x);
	while (move != NULL)
	{
		if (map[y][x] == 'C')
		{
			c--;
			printf("COIN");
		}
		else if (map[y][x] == 'E')
			e++;
		if (c == 0 && e == 1)
			return ;
		ft_printf("char = %c\n", map[y][x]);
		map[y][x] = 'V';
		if (map[y][x + 1] != '1' && map[y][x + 1] != 'V')
		{
			printf("right, x=%d y=%d\n\n", x, y);
			newnode(&move, y, x++);
		}
		else if (map[y - 1][x] != '1' && map[y - 1][x] != 'V')
		{
			printf("Down, x=%d y=%d\n\n", x, y);
			newnode(&move, y--, x);
		}
		else if (map[y][x - 1] != '1' && map[y][x - 1] != 'V')
		{
			printf("Up, x=%d y=%d\n\n", x, y);
			newnode(&move, y, x--);
		}
		else if (map[y + 1][x] != '1' && map[y + 1][x] != 'V')
		{
			ft_printf("Left, x=%d y=%d\n\n", x, y);
			newnode(&move, y++, x);
		}
		else
		{
			if (move->prev == NULL)
				ft_error(v, "Error\nMap is undoable.\n");
			ft_printf("backtrack\n\n");
			tmp = move;
			move = move->prev;
			free(tmp);
			y = move->y;
			x = move->x;
		}
	}
	//Free map;
}


/*
void	check_doable_ext(t_vars *v, char **map, t_node *move)
{
	t_node	*tmp;

	if (v->pfy - 1 > 0 && map[v->pfy - 1][v->pfx] != '1' && map[v->pfy - 1][v->pfx] != 'V')
		newnode(&move, v->pfy--, v->pfx);
	else if (v->pfx - 1 > 0 && map[v->pfy][v->pfx - 1] != '1' && map[v->pfy][v->pfx - 1] != 'V')
		newnode(&move, v->pfy, v->pfx--);
	else if (v->pfy + 1 < v->map_y && map[v->pfy + 1][v->pfx] != '1' && map[v->pfy + 1][v->pfx] != 'V')
		newnode(&move, v->pfy++, v->pfx);
	else if (v->pfx + 1 < v->map_x && map[v->pfy][v->pfx + 1] != '1' && map[v->pfy][v->pfx + 1] != 'V')
		newnode(&move, v->pfy, v->pfx++);
	else
	{
		if (move->prev == NULL)
			ft_error(v, "Error\nMap is undoable.\n");
		tmp = move;
		move = move->prev;
		free(tmp);
		v->pfy = move->y;
		v->pfx = move->x;
	}
}

void	check_if_doable(t_vars *v)
{
	t_node	*move;
	char	**map;
	int		c;
	int		e;

	map = create_map(v);
	move = NULL;
	c = v->collec;
	e = 0;
	v->pfx = v->p_x;
	v->pfy = v->p_y;
	newnode(&move, v->pfy, v->pfx);
	while (move != NULL)
	{
		if (map[v->pfy][v->pfx] == 'C')
			c--;
		else if (map[v->pfy][v->pfx] == 'E')
			e++;
		if (c == 0 && e == 1)
			return ;
		map[v->pfy][v->pfx] = 'V';
		check_doable_ext(v, map, move);
	}
}
*/