/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:31 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/14 18:25:39 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_put_win(t_vars *v, int x, int y, void *sprite)
{
	mlx_put_image_to_window(v->mlx, v->win, sprite, IMG_SIZE * x, IMG_SIZE * y);
}

int	ft_strlen_n(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (--i);
}

void	display_moves(t_vars *v)
{
	char	*str;

	str = ft_itoa(v->moves++);
	ft_putstr_fd("Moves: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	free(str);
}

void	check_map_ext(t_vars *v)
{
	int		i;
	char	*ext;

	i = 1;
	ext = ".ber";
	if (ft_strlen(v->mapname) < 5 || \
		v->mapname[ft_strlen(v->mapname) - 1] == '/')
	{
		ft_error(v, "Error\nNo map name, you tried to have me, " \
			"big dinguo that you are!\n");
	}
	while (++i < 5)
		if (v->mapname[ft_strlen(v->mapname) - i] != ext[4 - i])
			ft_error(v, "Error\nProblem with map extension.\n");
}
