/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:52:00 by rlaforge          #+#    #+#             */
/*   Updated: 2022/10/13 15:13:34 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_game(t_vars *vars)
{
	free_map(vars, vars->map);
	free_img(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

void	exit_game_light(t_vars *vars, int map)
{
	if (map)
		free_map(vars, vars->map);
	free_img(vars);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

void	free_map(t_vars *vars, char **map)
{
	int	y;

	y = 0;
	while (y < vars->map_y)
		free(map[y++]);
	free(map);
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
	mlx_destroy_image(v->mlx, v->sprites.w);
	mlx_destroy_image(v->mlx, v->sprites.e);
	mlx_destroy_image(v->mlx, v->sprites.c);
	mlx_destroy_image(v->mlx, v->sprites.f);
	mlx_destroy_image(v->mlx, v->sprites.p);
}
