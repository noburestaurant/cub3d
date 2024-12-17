/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:13:15 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 03:14:56 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_ray_facing_up(float ray_angle)
{
	return (sin(ray_angle) > 0);
}

int	is_ray_facing_down(float ray_angle)
{
	return (sin(ray_angle) < 0);
}

int	is_ray_facing_right(float ray_angle)
{
	return (cos(ray_angle) > 0);
}

int	is_ray_facing_left(float ray_angle)
{
	return (cos(ray_angle) < 0);
}

int	has_wall_at(t_vars *vars, int next_horizontal_touch_x,
	int next_horizontal_touch_y)
{
	int	coordinate_x_in_map;
	int	coordinate_y_in_map;

	coordinate_x_in_map = next_horizontal_touch_x / TILE_SIZE;
	coordinate_y_in_map = next_horizontal_touch_y / TILE_SIZE;
	return (vars->map[coordinate_y_in_map][coordinate_x_in_map] == '1');
}

double	calculate_distance_between_two_points(int a_x, int a_y,
	int b_x, int b_y)
{
	int	delta_x;
	int	delta_y;

	delta_x = b_x - a_x;
	delta_y = b_y - a_y;
	return (sqrt((delta_x) * (delta_x) + (delta_y) * (delta_y)));
}
