/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:13:15 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 14:11:07 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calculate_distance_between_two_points(int a_x, int a_y,
	int b_x, int b_y)
{
	int	delta_x;
	int	delta_y;

	delta_x = b_x - a_x;
	delta_y = b_y - a_y;
	return (sqrtf((delta_x) * (delta_x) + (delta_y) * (delta_y)));
}

float	distance_vert_is_smallest(t_vars *vars, float distance_vert)
{
	vars->ray.wall_hit_x = vars->ray.vert_wall_hit_x;
	vars->ray.wall_hit_y = vars->ray.vert_wall_hit_y;
	return (distance_vert);
}

float	distance_horz_is_smallest(t_vars *vars, float distance_horz)
{
	vars->ray.wall_hit_x = vars->ray.horz_wall_hit_x;
	vars->ray.wall_hit_y = vars->ray.horz_wall_hit_y;
	return (distance_horz);
}

float	handle_distance_comparison(t_vars *vars, float distance_horz,
		float distance_vert)
{
	if (distance_horz == 0 && distance_vert == 0)
	{
		printf("both distance variable is zero!\n");
		return (0);
	}
	vars->render_info.horizontal_plane = 0;
	if (distance_horz == 0)
		return (distance_vert_is_smallest(vars, distance_vert));
	else if (distance_vert == 0)
	{
		vars->render_info.horizontal_plane = 1;
		return (distance_horz_is_smallest(vars, distance_horz));
	}
	if (distance_horz > distance_vert)
		return (distance_vert_is_smallest(vars, distance_vert));
	else
	{
		vars->render_info.horizontal_plane = 1;
		return (distance_horz_is_smallest(vars, distance_horz));
	}
}

int	is_in_bounds(t_ray_calc *calc)
{
	return (0 <= calc->vals[0] && calc->vals[0] <= WINDOW_WIDTH
		&& 0 <= calc->vals[1] && calc->vals[1] <= WINDOW_HEIGHT);
}
