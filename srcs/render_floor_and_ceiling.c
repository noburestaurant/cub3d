/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 01:53:13 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 03:00:28 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_floor(t_vars *vars, int floor_color)
{
	int	put_pixel_x;
	int	put_pixel_y;

	put_pixel_y = 0;
	while (put_pixel_y < WINDOW_HEIGHT / 2)
	{
		put_pixel_x = 0;
		while (put_pixel_x < WINDOW_WIDTH)
		{
			mlx_pixel_put(vars->mlx, vars->win,
				put_pixel_x, put_pixel_y, floor_color);
			put_pixel_x++;
		}
		put_pixel_y++;
	}
}

void	render_ceiling(t_vars *vars, int ceiling_color)
{
	int	put_pixel_x;
	int	put_pixel_y;

	put_pixel_y = WINDOW_HEIGHT / 2;
	while (put_pixel_y < WINDOW_HEIGHT)
	{
		put_pixel_x = 0;
		while (put_pixel_x < WINDOW_WIDTH)
		{
			mlx_pixel_put(vars->mlx, vars->win,
				put_pixel_x, put_pixel_y, ceiling_color);
			put_pixel_x++;
		}
		put_pixel_y++;
	}
}

void	render_floor_and_ceiling(t_vars *vars)
{
	int	floor_color;
	int	ceiling_color;

	floor_color = 0xff0000;
	ceiling_color = 0x00ff00;
	render_floor(vars, floor_color);
	render_ceiling(vars, ceiling_color);
}
