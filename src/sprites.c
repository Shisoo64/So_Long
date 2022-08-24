/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:57:41 by rlaforge          #+#    #+#             */
/*   Updated: 2022/08/24 15:22:25 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_sprites_walls(t_sprites *s, t_vars v)
{
	int			ix;
	int			iy;

	s->w = mlx_xpm_file_to_image(v.mlx, "./sprt/wall0.xpm", &ix, &iy);
	s->w_u = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_up.xpm", &ix, &iy);
	s->w_ul = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_upl.xpm", &ix, &iy);
	s->w_ur = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_upr.xpm", &ix, &iy);
	s->w_l = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_left.xpm", &ix, &iy);
	s->w_r = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_right.xpm", &ix, &iy);
	s->w_d = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_down.xpm", &ix, &iy);
	s->w_dl = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_downl.xpm", &ix, &iy);
	s->w_dr = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_downr.xpm", &ix, &iy);
}

t_sprites	get_sprites(t_vars v)
{
	t_sprites	s;
	int			ix;
	int			iy;

	s.f = mlx_xpm_file_to_image(v.mlx, "sprt/floor.xpm", &ix, &iy);
	s.c = mlx_xpm_file_to_image(v.mlx, "./sprt/collec0.xpm", &ix, &iy);
	s.p = mlx_xpm_file_to_image(v.mlx, "./sprt/pright0.xpm", &ix, &iy);
	s.e = mlx_xpm_file_to_image(v.mlx, "./sprt/exit1.xpm", &ix, &iy);
	get_sprites_walls(&s, v);
	return (s);
}

void	print_wall(t_vars *v, int x, int y)
{
	if (y == 0)
	{
		if (x == 0)
			ft_put_win(v, x, y, v->sprites.w_ul);
		else if (x == v->map_x)
			ft_put_win(v, x, y, v->sprites.w_ur);
		else
			ft_put_win(v, x, y, v->sprites.w_u);
	}
	else if (y == v->map_y - 1)
	{
		if (x == 0)
			ft_put_win(v, x, y, v->sprites.w_dl);
		else if (x == v->map_x)
			ft_put_win(v, x, y, v->sprites.w_dr);
		else
			ft_put_win(v, x, y, v->sprites.w_d);
	}
	else if (x == 0)
		ft_put_win(v, x, y, v->sprites.w_l);
	else if (x == v->map_x)
		ft_put_win(v, x, y, v->sprites.w_r);
	else
		ft_put_win(v, x, y, v->sprites.w);
}
