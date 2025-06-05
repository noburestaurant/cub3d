/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_geometry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 13:33:09 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line_step(t_vars *vars, t_line_data *data)
{
	int	e2;

	mlx_pixel_put(vars->mlx, vars->win, data->x_a, data->y_a, 0xFFFFFF);
	if (data->x_a == data->x_b && data->y_a == data->y_b)
	{
		data->done = 1;
		return ;
	}
	e2 = data->err * 2;
	if (e2 > -data->dy)
	{
		data->err -= data->dy;
		data->x_a += data->sx;
	}
	if (e2 < data->dx)
	{
		data->err += data->dx;
		data->y_a += data->sy;
	}
}

void	line(t_vars *vars, t_line_params params)
{
	t_line_data	data;

	data.x_a = params.x_a;
	data.y_a = params.y_a;
	data.x_b = params.x_b;
	data.y_b = params.y_b;
	data.dx = abs(params.x_b - params.x_a);
	data.dy = abs(params.y_b - params.y_a);
	if (params.x_a < params.x_b)
		data.sx = 1;
	else
		data.sx = -1;
	if (params.y_a < params.y_b)
		data.sy = 1;
	else
		data.sy = -1;
	data.err = data.dx - data.dy;
	data.done = 0;
	while (!data.done)
		draw_line_step(vars, &data);
}

void	circle(t_vars *vars, int cx, int cy)
{
	int	radius;
	int	x;
	int	y;

	radius = 6;
	y = -1 * radius;
	while (y <= radius)
	{
		x = -1 * radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_pixel_put(vars->mlx, vars->win, cx + x, cy + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

float	normalize_angle(float angle)
{
	float	two_pi;

	two_pi = PI * 2;
	angle = fmod(angle, two_pi);
	if (angle < 0)
		angle += two_pi;
	return (angle);
}

int	is_equal(float a, float b)
{
	return (fabs(a - b) < 0.001);
}
