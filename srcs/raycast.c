/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 03:13:37 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 03:15:19 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calculate_wall_hit_distance_horizontal(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	int		next_horizontal_touch_x;
	int		next_horizontal_touch_y;

	// calculate yintercept
	yintercept = (yplayer / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		yintercept += TILE_SIZE;
	// calculate xintercept
	xintercept = xplayer + ((yplayer - yintercept) / tan(ray_angle));
	// calculate ystep
	ystep = TILE_SIZE;
	if (is_ray_facing_up(ray_angle))
		ystep *= -1;
	// calculate xstep
	xstep = ystep / tan(ray_angle);
	if (is_ray_facing_left(ray_angle) && xstep > 0)
		xstep *= -1;
	if (is_ray_facing_right(ray_angle) && xstep < 0)
		xstep *= -1;
	// increment xstep and ystep until we find a wall
	next_horizontal_touch_x = xintercept;
	next_horizontal_touch_y = yintercept;
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
			// increment xstep and ystep
			next_horizontal_touch_x += xstep;
			next_horizontal_touch_y += ystep;
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
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	int		next_vertical_touch_x;
	int		next_vertical_touch_y;

	// calculate xintercept
	xintercept = xplayer / TILE_SIZE * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		xintercept += TILE_SIZE;
	// calculate yintercept
	yintercept = yplayer - ((xintercept - xplayer) * tan(ray_angle));
	// calculate xstep
	xstep = TILE_SIZE;
	if (is_ray_facing_left(ray_angle) && xstep > 0)
		xstep *= -1;
	// calculate ystep
	ystep = xstep * tan(ray_angle);
	if (is_ray_facing_up(ray_angle) && ystep > 0)
		ystep *= -1;
	if (is_ray_facing_down(ray_angle) && ystep < 0)
		ystep *= -1;
	// increment xstep and ystep until we find a wall
	next_vertical_touch_x = xintercept;
	next_vertical_touch_y = yintercept;
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
			// increment xstep and ystep
			next_vertical_touch_x += xstep;
			next_vertical_touch_y += ystep;
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
