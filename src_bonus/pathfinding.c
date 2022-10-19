/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:53:21 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/19 15:01:43 by rlaforge         ###   ########.fr       */
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
	if (!head || !*head)
	{
		*head = node;
		return ;
	}
	node->prev = *head;
	*head = node;
}

void	free_pathfinding(t_vars *v, t_node **head, char **map)
{
	t_node	*tmp;

	while ((*head)->prev)
	{
		tmp = *head;
		*head = (*head)->prev;
		free(tmp);
	}
	free(*head);
	free_map(v, map);
}

void	check_doable_ext(t_vars *v, char **map, t_node **move)
{
	t_node	*tmp;

	map[v->vy][v->vx] = 'V';
	if (map[v->vy][v->vx + 1] != '1' && map[v->vy][v->vx + 1] != 'V')
		newnode(move, v->vy, ++v->vx);
	else if (map[v->vy - 1][v->vx] != '1' && map[v->vy - 1][v->vx] != 'V')
		newnode(move, --v->vy, v->vx);
	else if (map[v->vy][v->vx - 1] != '1' && map[v->vy][v->vx - 1] != 'V')
		newnode(move, v->vy, --v->vx);
	else if (map[v->vy + 1][v->vx] != '1' && map[v->vy + 1][v->vx] != 'V')
		newnode(move, ++v->vy, v->vx);
	else
	{
		if ((*move)->prev == NULL)
		{
			ft_putstr_fd("Error\nMap is undoable.\n", 2);
			free_pathfinding(v, move, map);
			exit_game(v);
		}
		tmp = *move;
		*move = (*move)->prev;
		free(tmp);
		v->vy = (*move)->y;
		v->vx = (*move)->x;
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
	v->vx = v->p_x;
	v->vy = v->p_y;
	newnode(&move, v->vy, v->vx);
	while (move != NULL)
	{
		if (map[v->vy][v->vx] == 'C')
			c--;
		else if (map[v->vy][v->vx] == 'E')
			e++;
		if (c == 0 && e == 1)
		{
			free_pathfinding(v, &move, map);
			return ;
		}
		check_doable_ext(v, map, &move);
	}
}
