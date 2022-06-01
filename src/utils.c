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

void	ft_count(int n, int i[2])
{
	int	x;

	i[0] = 1;
	i[1] = 0;
	if (n < 0)
		i[1]++;
	x = n;
	while (x >= 10 || x <= -10)
	{
		x /= 10;
		i[0]++;
	}
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		i[2];

	ft_count(n, i);
	if (i[1])
		n = -n;
	tab = malloc(sizeof(char) * ((i[0] += i[1]) + 1));
	if (!tab)
		return (NULL);
	tab[i[0]] = '\0';
	while (i[0]--)
	{
		tab[i[0]] = (n % 10) + '0';
		n /= 10;
	}
	if (i[1])
		tab[0] = '-';
	return (tab);
}
