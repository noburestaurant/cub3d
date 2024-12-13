/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:38 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/13 15:34:54 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_walk_direction(t_vars *vars)
{
	int		line_of_len;
	int		x_window;
	int		y_window;
	float	angle;

	x_window = vars->player.x * 50 + (TILE_SIZE / 2);
	y_window = vars->player.y * 50 + (TILE_SIZE / 2);
	angle = normalize_angle(vars->player.rotation_angle);
	line_of_len = 100;
	line(vars,
		x_window,
		y_window,
		x_window + (line_of_len * cos(angle)),
		y_window - (line_of_len * sin(angle)));
}

void	choose_image(t_vars *vars, int x, int y)
{
	if (vars->map[y][x] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img_renga, x * 50, y * 50);
	else
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img_grass, x * 50, y * 50);
	// else if (vars->map[y][x] == '0')
	// 	mlx_put_image_to_window(vars->mlx, vars->win,
	// 		vars->img_grass, x * 50, y * 50);
	// else if (check_player(vars->map[y][x]))
	// {
	// 	mlx_put_image_to_window(vars->mlx, vars->win,
	// 		vars->img_grass, x * 50, y * 50);
	// 	circle(vars, (x * 50 + (TILE_SIZE / 2)), (y * 50 + (TILE_SIZE / 2)));
	// 	orientation(vars);
	// 	// put_walk_direction(vars); // test
	// }
}

void	print_player(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			if (check_player(vars->map[y][x]))
			{
				circle(vars, (x * 50 + (TILE_SIZE / 2)),
					(y * 50 + (TILE_SIZE / 2)));
				orientation(vars);
				put_walk_direction(vars);
			}
			x++;
		}
		y++;
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
	print_player(vars);
}
