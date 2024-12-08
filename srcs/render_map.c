/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:38 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/08 18:58:13 by retanaka         ###   ########.fr       */
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
	else if (check_player(vars->map[y][x]))
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img_player.current, x * 50, y * 50);
}

void	render_vertical_line(t_vars *vars, int len, int x)
{
	int	i;
	int	y;

	y = HEIGHT / 2 - len * 10;
	i = 0;
	while (i < len * 20)
	{
		y++;
		mlx_pixel_put(vars->mlx, vars->win, x, y, 0xffffff);
		i++;
	}
}

int	get_length(t_vars *vars, float angle)
{
	(void)angle;
	(void)vars;
	return (1);
}

void	render_map(t_vars *vars)
{
	int	x;
	int	y;
	float	angle;

	angle = 0.0;
	if (vars->player.ort == 'N')
		angle = 0;
	else if (vars->player.ort == 'E')
		angle = 90;
	else if (vars->player.ort == 'S')
		angle = 180;
	else if (vars->player.ort == 'W')
		angle = 270;
	angle -= FOV / 2;
	x = 0;
	while (x < WIDTH)
	{
		render_vertical_line(vars, get_length(vars, angle), x);
		angle += (float)FOV / (float)WIDTH;
		x++;
	}

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
