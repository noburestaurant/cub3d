/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:26 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:56:40 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_rotation_angle(char c)
{
	if (c == 'E')
		return (0);
	else if (c == 'N')
		return (PI / 2);
	else if (c == 'W')
		return (PI);
	else
		return ((PI * 3) / 2);
}

void	line(t_vars *vars, int x_a, int y_a, int x_b, int y_b)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x_b - x_a);
	dy = abs(y_b - y_a);
	sx = (x_a < x_b) ? 1 : -1;
	sy = (y_a < y_b) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		mlx_pixel_put(vars->mlx, vars->win, x_a, y_a, 0xFFFFFF);
		if (x_a == x_b && y_a == y_b)
			break ;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x_a += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y_a += sy;
		}
	}
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

void	print_orientation(t_vars *vars) // test code
{
	vars->player.rotation_angle = normalize_angle(vars->player.rotation_angle);
	// if (is_equal(vars->player.rotation_angle, 0))
	// 	printf("orientation: east\n");
	// else if (is_equal(vars->player.rotation_angle, (PI / 2)))
	// 	printf("orientation: north\n");
	// else if (is_equal(vars->player.rotation_angle, PI))
	// 	printf("orientation: west\n");
	// else if (is_equal(vars->player.rotation_angle, (PI * 3 / 2)))
	// 	printf("orientation: south\n");
}
