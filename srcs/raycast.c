/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:13:37 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 09:09:31 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calculate_wall_hit_distance_horizontal(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	// float	xstep;
	// float	ystep;
	// float	xintercept;
	// float	yintercept;
	int		next_horizontal_touch_x;
	int		next_horizontal_touch_y;

	vars->ray.yintercept = (yplayer / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		vars->ray.yintercept += TILE_SIZE;
	vars->ray.xintercept = xplayer + ((yplayer - vars->ray.yintercept) / tan(ray_angle));
	vars->ray.ystep = TILE_SIZE;
	if (is_ray_facing_up(ray_angle))
		vars->ray.ystep *= -1;
	vars->ray.xstep = vars->ray.ystep / tan(ray_angle);
	if (is_ray_facing_left(ray_angle) && vars->ray.xstep > 0)
		vars->ray.xstep *= -1;
	if (is_ray_facing_right(ray_angle) && vars->ray.xstep < 0)
		vars->ray.xstep *= -1;
	next_horizontal_touch_x = vars->ray.xintercept;
	next_horizontal_touch_y = vars->ray.yintercept;
	vars->ray.horz_wall_hit_x = 0;
	vars->ray.horz_wall_hit_y = 0;
	vars->ray.found_horz_wall = 0;
	while (0 <= next_horizontal_touch_x && next_horizontal_touch_x <= WINDOW_WIDTH
		&& 0 <= next_horizontal_touch_y && next_horizontal_touch_y <= WINDOW_HEIGHT)
	{
		if (has_wall_at(vars, next_horizontal_touch_x, next_horizontal_touch_y - (is_ray_facing_up(ray_angle))))
		{
			vars->ray.found_horz_wall = 1;
			vars->ray.horz_wall_hit_x = next_horizontal_touch_x;
			vars->ray.horz_wall_hit_y = next_horizontal_touch_y;
			break ;
		}
		else
		{
			// increment vars->ray.xstep and vars->ray.ystep
			next_horizontal_touch_x += vars->ray.xstep;
			next_horizontal_touch_y += vars->ray.ystep;
		}
	}
	if (vars->ray.found_horz_wall != 1)
		return (0);
	return (calculate_distance_between_two_points(xplayer, yplayer,
		vars->ray.horz_wall_hit_x, vars->ray.horz_wall_hit_y));
}

float	calculate_wall_hit_distance_vertical(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	int		next_vertical_touch_x;
	int		next_vertical_touch_y;

	vars->ray.xintercept = xplayer / TILE_SIZE * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		vars->ray.xintercept += TILE_SIZE;
	vars->ray.yintercept = yplayer - ((vars->ray.xintercept - xplayer) * tan(ray_angle));
	vars->ray.xstep = TILE_SIZE;
	if (is_ray_facing_left(ray_angle) && vars->ray.xstep > 0)
		vars->ray.xstep *= -1;
	vars->ray.ystep = vars->ray.xstep * tan(ray_angle);
	if (is_ray_facing_up(ray_angle) && vars->ray.ystep > 0)
		vars->ray.ystep *= -1;
	if (is_ray_facing_down(ray_angle) && vars->ray.ystep < 0)
		vars->ray.ystep *= -1;
	next_vertical_touch_x = vars->ray.xintercept;
	next_vertical_touch_y = vars->ray.yintercept;
	vars->ray.vert_wall_hit_x = 0;
	vars->ray.vert_wall_hit_y = 0;
	vars->ray.found_vert_wall = 0;
	while (0 <= next_vertical_touch_x && next_vertical_touch_x < WINDOW_WIDTH
		&& 0 <= next_vertical_touch_y && next_vertical_touch_y < WINDOW_HEIGHT)
	{
		if (has_wall_at(vars, next_vertical_touch_x - (is_ray_facing_left(ray_angle)), next_vertical_touch_y))
		{
			vars->ray.found_vert_wall = 1;
			vars->ray.vert_wall_hit_x = next_vertical_touch_x;
			vars->ray.vert_wall_hit_y = next_vertical_touch_y;
			break ;
		}
		else
		{
			// increment vars->ray.xstep and vars->ray.ystep
			next_vertical_touch_x += vars->ray.xstep;
			next_vertical_touch_y += vars->ray.ystep;
		}
	}
	if (vars->ray.found_vert_wall != 1)
		return (0);
	return (calculate_distance_between_two_points(xplayer, yplayer,
		vars->ray.vert_wall_hit_x, vars->ray.vert_wall_hit_y));
}

int	raycast(t_vars *vars, float ray_angle, int xplayer, int yplayer)
{
	float	len;
	float	distance_horz;
	float	distance_vert;

	len = 0;
	distance_horz = calculate_wall_hit_distance_horizontal
		(vars, ray_angle, xplayer, yplayer);
	distance_vert = calculate_wall_hit_distance_vertical
		(vars, ray_angle, xplayer, yplayer);
	if (distance_horz == 0 || distance_vert == 0)
	{
		if (distance_horz == 0)
		{
			vars->ray.wall_hit_x = vars->ray.vert_wall_hit_x;
			vars->ray.wall_hit_y = vars->ray.vert_wall_hit_y;
			return (distance_vert);
		}
		else if (distance_vert == 0)
		{
			vars->ray.wall_hit_x = vars->ray.horz_wall_hit_x;
			vars->ray.wall_hit_y = vars->ray.horz_wall_hit_y;
			return (distance_horz);
		}
	}
	if (distance_horz > distance_vert)
	{
		vars->ray.wall_hit_x = vars->ray.vert_wall_hit_x;
		vars->ray.wall_hit_y = vars->ray.vert_wall_hit_y;
		len = distance_vert;
	}
	else
	{
		vars->ray.wall_hit_x = vars->ray.horz_wall_hit_x;
		vars->ray.wall_hit_y = vars->ray.horz_wall_hit_y;
		len = distance_horz;
	}
	return (len);
}
