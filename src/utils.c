/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:31 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/01 20:07:07 by rlaforge         ###   ########.fr       */
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
	while (s[i] != '\n' && s[i++])
		;
	return (--i);
}

void	display_moves(t_vars *v)
{
	char	*str;

	str = ft_itoa(v->moves++);
	ft_put_win(v, 1, v->map_y - 1, v->sprites.w_d);
	ft_put_win(v, 2, v->map_y - 1, v->sprites.w_d);
	mlx_string_put(v->mlx, v->win, IMG_SIZE + 5,
		(v->map_y) * IMG_SIZE - 10, 0xffffff, "Moves:");
	mlx_string_put(v->mlx, v->win, IMG_SIZE + 45,
		(v->map_y) * IMG_SIZE - 10, 0xffffff, str);
	free(str);
}

void	check_map_ext(t_vars *v)
{
	int		i;
	char	*ext;

	i = 1;
	ext = ".ber";
	while (++i < 5)
		if (v->mapname[ft_strlen(v->mapname) - i] != ext[4 - i])
			ft_error(v, "Error\nProblem with map extension.\n");
}
