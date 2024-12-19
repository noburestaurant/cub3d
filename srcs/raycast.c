/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:13:37 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 16:57:57by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_step_and_intercept_horizontal(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	vars->ray.yintercept = (yplayer / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		vars->ray.yintercept += TILE_SIZE;
	vars->ray.xintercept = xplayer + ((yplayer - vars->ray.yintercept)
			/ tan(ray_angle));
	vars->ray.ystep = TILE_SIZE;
	if (is_ray_facing_up(ray_angle))
		vars->ray.ystep *= -1;
	vars->ray.xstep = vars->ray.ystep / tan(ray_angle);
	if (is_ray_facing_left(ray_angle) && vars->ray.xstep > 0)
		vars->ray.xstep *= -1;
	if (is_ray_facing_right(ray_angle) && vars->ray.xstep < 0)
		vars->ray.xstep *= -1;
}

float	calculate_wall_hit_distance_horizontal(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	float		next_horz_touch_x;
	float		next_horz_touch_y;

	calc_step_and_intercept_horizontal(vars, ray_angle, xplayer, yplayer);
	next_horz_touch_x = vars->ray.xintercept;
	next_horz_touch_y = vars->ray.yintercept;
	vars->ray.found_horz_wall = 0;
	while (0 <= next_horz_touch_x && next_horz_touch_x < WINDOW_WIDTH
		&& 0 <= next_horz_touch_y && next_horz_touch_y < WINDOW_HEIGHT)
	{
		// printf("next_horz_touch_x = %f\n", next_horz_touch_x);
		// printf("next_horz_touch_y = %f\n", next_horz_touch_y);
		if (has_wall_at(vars, floorf(next_horz_touch_x), floorf(next_horz_touch_y)
				- (is_ray_facing_up(ray_angle))))
		{
			vars->ray.found_horz_wall = 1;
			vars->ray.horz_wall_hit_x = next_horz_touch_x;
			vars->ray.horz_wall_hit_y = next_horz_touch_y;
			break ;
		}
		next_horz_touch_x += vars->ray.xstep;
		next_horz_touch_y += vars->ray.ystep;
	}
	if (vars->ray.found_horz_wall != 1)
		return (0);
	return (calculate_distance_between_two_points(xplayer, yplayer,
			vars->ray.horz_wall_hit_x, vars->ray.horz_wall_hit_y));
}

void	calc_step_and_intercept_vertical(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	vars->ray.xintercept = xplayer / TILE_SIZE * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		vars->ray.xintercept += TILE_SIZE;
	vars->ray.yintercept = yplayer - ((vars->ray.xintercept - xplayer)
			* tan(ray_angle));
	vars->ray.xstep = TILE_SIZE;
	if (is_ray_facing_left(ray_angle) && vars->ray.xstep > 0)
		vars->ray.xstep *= -1;
	vars->ray.ystep = vars->ray.xstep * tan(ray_angle);
	if (is_ray_facing_up(ray_angle) && vars->ray.ystep > 0)
		vars->ray.ystep *= -1;
	if (is_ray_facing_down(ray_angle) && vars->ray.ystep < 0)
		vars->ray.ystep *= -1;
}

float	calculate_wall_hit_distance_vertical(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	float		next_vert_touch_x;
	float		next_vert_touch_y;

	calc_step_and_intercept_vertical(vars, ray_angle, xplayer, yplayer);
	next_vert_touch_x = vars->ray.xintercept;
	next_vert_touch_y = vars->ray.yintercept;
	vars->ray.found_vert_wall = 0;
	while (0 <= next_vert_touch_x && next_vert_touch_x < WINDOW_WIDTH
		&& 0 <= next_vert_touch_y && next_vert_touch_y < WINDOW_HEIGHT)
	{
		if (has_wall_at(vars, floorf(next_vert_touch_x)
				- (is_ray_facing_left(ray_angle)), floorf(next_vert_touch_y)))
		{
			vars->ray.found_vert_wall = 1;
			vars->ray.vert_wall_hit_x = next_vert_touch_x;
			vars->ray.vert_wall_hit_y = next_vert_touch_y;
			break ;
		}
		next_vert_touch_x += vars->ray.xstep;
		next_vert_touch_y += vars->ray.ystep;
	}
	if (vars->ray.found_vert_wall != 1)
		return (0);
	return (calculate_distance_between_two_points(xplayer, yplayer,
			vars->ray.vert_wall_hit_x, vars->ray.vert_wall_hit_y));
}

float	raycast(t_vars *vars, float ray_angle, int xplayer, int yplayer)
{
	float	distance_horz;
	float	distance_vert;

	vars->ray.wall_hit_x = 0;
	vars->ray.wall_hit_y = 0;
	distance_horz = 0;
	distance_vert = 0;
	distance_horz = calculate_wall_hit_distance_horizontal
		(vars, ray_angle, xplayer, yplayer);
	distance_vert = calculate_wall_hit_distance_vertical
		(vars, ray_angle, xplayer, yplayer);
	if (distance_horz == 0 && distance_vert == 0)
	{
		printf("both distance variable is zero!\n");
		// write(2, "Unknown error in raycast func\n", 31);
		// exit (2);
		return (0);
	}
	printf("distance_horz = %f\n", distance_horz);
	printf("distance_vert = %f\n", distance_vert);
	// printf("distance_horz = %.2f\n", distance_horz);
	// printf("distance_vert = %.2f\n", distance_vert);
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
