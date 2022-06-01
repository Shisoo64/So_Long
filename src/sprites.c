/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:57:41 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/01 15:45:52 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	s.w = mlx_xpm_file_to_image(v.mlx, "./sprt/wall.xpm", &ix, &iy);
	s.w_u = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_up.xpm", &ix, &iy);
	s.w_ul = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_upleft.xpm", &ix, &iy);
	s.w_ur = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_upright.xpm", &ix, &iy);
	s.w_l = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_left.xpm", &ix, &iy);
	s.w_r = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_right.xpm", &ix, &iy);
	s.w_d = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_down.xpm", &ix, &iy);
	s.w_dl = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_downleft.xpm", &ix, &iy);
	s.w_dr = mlx_xpm_file_to_image(v.mlx, "./sprt/wall_downright.xpm", &ix, &iy);
	return (s);
}

void	print_wall(t_vars *v, int x, int y)
{
	if (y == 0)
	{
		if (x == 0)
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_ul, IMG_SIZE * x, IMG_SIZE * y);
		else if (x == v->map_x - 1)
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_ur, IMG_SIZE * x, IMG_SIZE * y);
		else
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_u, IMG_SIZE * x, IMG_SIZE * y);
	}
	else if (y == v->map_y - 2)
	{
		if (x == 0)
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_dl, IMG_SIZE * x, IMG_SIZE * y);
		else if (x == v->map_x - 1)
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_dr, IMG_SIZE * x, IMG_SIZE * y);
		else
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_d, IMG_SIZE * x, IMG_SIZE * y);
	}
	else if (x == 0)
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_l, IMG_SIZE * x, IMG_SIZE * y);
	else if (x == v->map_x - 1)
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w_r, IMG_SIZE * x, IMG_SIZE * y);
	else
			mlx_put_image_to_window(v->mlx, v->win, v->sprites.w, IMG_SIZE * x, IMG_SIZE * y);
}
