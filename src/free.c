/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:52:00 by rlaforge          #+#    #+#             */
/*   Updated: 2022/06/28 19:52:01 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_game(t_vars *vars)
{
	free_map(vars);
	free_img(vars);
	free(vars->m_coord[0]);
	free(vars->m_coord[1]);
	free(vars->x_coord[0]);
	free(vars->x_coord[1]);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

void	exit_game_light(t_vars *vars, int map)
{
	if (map)
		free_map(vars);
	free_img(vars);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

void	free_map(t_vars *vars)
{
	int	y;

	y = 0;
	while (y < vars->map_y)
		free(vars->map[y++]);
	free(vars->map);
}

void	free_img(t_vars *v)
{
	mlx_destroy_image(v->mlx, v->sprites.w_u);
	mlx_destroy_image(v->mlx, v->sprites.w_ul);
	mlx_destroy_image(v->mlx, v->sprites.w_ur);
	mlx_destroy_image(v->mlx, v->sprites.w_l);
	mlx_destroy_image(v->mlx, v->sprites.w_r);
	mlx_destroy_image(v->mlx, v->sprites.w_d);
	mlx_destroy_image(v->mlx, v->sprites.w_dl);
	mlx_destroy_image(v->mlx, v->sprites.w_dr);
	mlx_destroy_image(v->mlx, v->sprites.w[0]);
	mlx_destroy_image(v->mlx, v->sprites.w[1]);
	mlx_destroy_image(v->mlx, v->sprites.w[2]);
	mlx_destroy_image(v->mlx, v->sprites.e[0]);
	mlx_destroy_image(v->mlx, v->sprites.e[1]);
	mlx_destroy_image(v->mlx, v->sprites.e[2]);
	mlx_destroy_image(v->mlx, v->sprites.c[0]);
	mlx_destroy_image(v->mlx, v->sprites.c[1]);
	mlx_destroy_image(v->mlx, v->sprites.c[2]);
	mlx_destroy_image(v->mlx, v->sprites.c[3]);
	mlx_destroy_image(v->mlx, v->sprites.f);
	mlx_destroy_image(v->mlx, v->sprites.win);
	free_enemies(v);
}

void	free_enemies(t_vars *v)
{
	mlx_destroy_image(v->mlx, v->sprites.p_l[0]);
	mlx_destroy_image(v->mlx, v->sprites.p_l[1]);
	mlx_destroy_image(v->mlx, v->sprites.p_l[2]);
	mlx_destroy_image(v->mlx, v->sprites.p_l[3]);
	mlx_destroy_image(v->mlx, v->sprites.p_r[0]);
	mlx_destroy_image(v->mlx, v->sprites.p_r[1]);
	mlx_destroy_image(v->mlx, v->sprites.p_r[2]);
	mlx_destroy_image(v->mlx, v->sprites.p_r[3]);
	mlx_destroy_image(v->mlx, v->sprites.x_l[0]);
	mlx_destroy_image(v->mlx, v->sprites.x_l[1]);
	mlx_destroy_image(v->mlx, v->sprites.x_l[2]);
	mlx_destroy_image(v->mlx, v->sprites.x_l[3]);
	mlx_destroy_image(v->mlx, v->sprites.x_r[0]);
	mlx_destroy_image(v->mlx, v->sprites.x_r[1]);
	mlx_destroy_image(v->mlx, v->sprites.x_r[2]);
	mlx_destroy_image(v->mlx, v->sprites.x_r[3]);
	mlx_destroy_image(v->mlx, v->sprites.m_l[0]);
	mlx_destroy_image(v->mlx, v->sprites.m_l[1]);
	mlx_destroy_image(v->mlx, v->sprites.m_l[2]);
	mlx_destroy_image(v->mlx, v->sprites.m_l[3]);
	mlx_destroy_image(v->mlx, v->sprites.m_r[0]);
	mlx_destroy_image(v->mlx, v->sprites.m_r[1]);
	mlx_destroy_image(v->mlx, v->sprites.m_r[2]);
	mlx_destroy_image(v->mlx, v->sprites.m_r[3]);
}
