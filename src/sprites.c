/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:57:41 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/01 20:19:31 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_sprites_extend(t_sprites *s, t_vars v)
{
	int			ix;
	int			iy;

	s->w = mlx_xpm_file_to_image(v.mlx, "./sprt/wall.xpm", &ix, &iy);
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
	s.c[0] = mlx_xpm_file_to_image(v.mlx, "./sprt/collec0.xpm", &ix, &iy);
	s.c[1] = mlx_xpm_file_to_image(v.mlx, "./sprt/collec1.xpm", &ix, &iy);
	s.c[2] = mlx_xpm_file_to_image(v.mlx, "./sprt/collec2.xpm", &ix, &iy);
	s.c[3] = mlx_xpm_file_to_image(v.mlx, "./sprt/collec3.xpm", &ix, &iy);
	s.p_u = mlx_xpm_file_to_image(v.mlx, "./sprt/playerup.xpm", &ix, &iy);
	s.p_d = mlx_xpm_file_to_image(v.mlx, "./sprt/playerdown.xpm", &ix, &iy);
	s.p_l = mlx_xpm_file_to_image(v.mlx, "./sprt/playerleft.xpm", &ix, &iy);
	s.p_r = mlx_xpm_file_to_image(v.mlx, "./sprt/playerright.xpm", &ix, &iy);
	s.e[0] = mlx_xpm_file_to_image(v.mlx, "./sprt/exit0.xpm", &ix, &iy);
	s.e[1] = mlx_xpm_file_to_image(v.mlx, "./sprt/exit1.xpm", &ix, &iy);
	s.e[2] = mlx_xpm_file_to_image(v.mlx, "./sprt/exit2.xpm", &ix, &iy);
	s.x_l = mlx_xpm_file_to_image(v.mlx, "./sprt/enemyleft.xpm", &ix, &iy);
	s.x_r = mlx_xpm_file_to_image(v.mlx, "./sprt/enemyright.xpm", &ix, &iy);
	get_sprites_extend(&s, v);
	return (s);
}

void	print_wall(t_vars *v, int x, int y)
{
	if (y == 0)
	{
		if (x == 0)
			ft_put_win(v, x, y, v->sprites.w_ul);
		else if (x == v->map_x - 1)
			ft_put_win(v, x, y, v->sprites.w_ur);
		else
			ft_put_win(v, x, y, v->sprites.w_u);
	}
	else if (y == v->map_y - 2)
	{
		if (x == 0)
			ft_put_win(v, x, y, v->sprites.w_dl);
		else if (x == v->map_x - 1)
			ft_put_win(v, x, y, v->sprites.w_dr);
		else
			ft_put_win(v, x, y, v->sprites.w_d);
	}
	else if (x == 0)
		ft_put_win(v, x, y, v->sprites.w_l);
	else if (x == v->map_x - 1)
		ft_put_win(v, x, y, v->sprites.w_r);
	else
		ft_put_win(v, x, y, v->sprites.w);
}
