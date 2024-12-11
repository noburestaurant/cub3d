/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:38 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/11 20:51:46 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_image(t_vars *vars, int x, int y)
{
	if (vars->map[y][x] == '0')
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img_grass, x * 50, y * 50);
	else if (vars->map[y][x] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img_renga, x * 50, y * 50);
	// else if (check_player(vars->map[y][x]))
	// 	mlx_put_image_to_window(vars->mlx, vars->win,
	// 		vars->img_player->current, x * 50, y * 50);
	else if (check_player(vars->map[y][x]))
	{
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img_grass, x * 50, y * 50);
		circle(vars, (x * 50 + (TILE_SIZE / 2)), (y * 50 + (TILE_SIZE / 2)));
		orientation(vars);
	}
}

void	render_map(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			choose_image(vars, x, y);
			x++;
		}
		y++;
	}
}
