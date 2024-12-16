/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:10 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/16 23:35:01 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calculate_wall_hit_distance_horizontal_delete(t_vars *vars, float ray_angle,
	int xplayer, int yplayer, float vals[2]) // test to delete
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	int		next_horizontal_touch_x;
	int		next_horizontal_touch_y;
	int		wall_hit_x;
	int		wall_hit_y;

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
	wall_hit_x = 0; // unnecessary
	wall_hit_y = 0; // unnecessary
	while (0 <= next_horizontal_touch_x && next_horizontal_touch_x <= WINDOW_WIDTH
		&& 0 <= next_horizontal_touch_y && next_horizontal_touch_y <= WINDOW_HEIGHT)
	{
		if (has_wall_at(vars, next_horizontal_touch_x, next_horizontal_touch_y - (is_ray_facing_up(ray_angle))))
		{
			wall_hit_x = next_horizontal_touch_x;
			wall_hit_y = next_horizontal_touch_y - (is_ray_facing_up(ray_angle));
			vals[0] = next_horizontal_touch_x;
			vals[1] = next_horizontal_touch_y - (is_ray_facing_up(ray_angle));
			break ;
		}
		else
		{
			// increment xstep and ystep
			next_horizontal_touch_x += xstep;
			next_horizontal_touch_y += ystep;
		}
	}
	if (wall_hit_x == 0 && wall_hit_y == 0)
		return (0);
	// calculate the distance froom point(xplayer, yplayer) to
	// 	point(wall_hit_x, wall_hit_y) and return it
	return (calculate_distance_between_two_points(xplayer, yplayer, wall_hit_x, wall_hit_y));
}

float	calculate_wall_hit_distance_vertical_delete(t_vars *vars, float ray_angle,
	int xplayer, int yplayer, float vals[2]) // test to delete
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	int		next_vertical_touch_x;
	int		next_vertical_touch_y;
	int		wall_hit_x;
	int		wall_hit_y;

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
	wall_hit_x = 0;
	wall_hit_y = 0;
	while (0 <= next_vertical_touch_x && next_vertical_touch_x < WINDOW_WIDTH
		&& 0 <= next_vertical_touch_y && next_vertical_touch_y < WINDOW_HEIGHT) // next_vertical_touch is in the window
	{
		if (has_wall_at(vars, next_vertical_touch_x - (is_ray_facing_left(ray_angle)), next_vertical_touch_y))
		{
			wall_hit_x = next_vertical_touch_x - (is_ray_facing_left(ray_angle));
			wall_hit_y = next_vertical_touch_y;
			vals[0] = next_vertical_touch_x - (is_ray_facing_left(ray_angle));
			vals[1] = next_vertical_touch_y;
			break ;
		}
		else
		{
			// increment xstep and ystep
			next_vertical_touch_x += xstep;
			next_vertical_touch_y += ystep;
		}
	}
	if (wall_hit_x == 0 && wall_hit_y == 0)
		return (0);
	return (calculate_distance_between_two_points(xplayer, yplayer, wall_hit_x, wall_hit_y));
}

void	render_ray(t_vars *vars, float ray_angle, int xplayer, int yplayer)
{
	float	distance_horz;
	float	distance_vert;
	float	horz_vals[2];
	float	vert_vals[2];

	horz_vals[0] = 0;
	vert_vals[1] = 0;
	distance_horz = calculate_wall_hit_distance_horizontal_delete(vars, ray_angle, xplayer, yplayer, horz_vals);
	distance_vert = calculate_wall_hit_distance_vertical_delete(vars, ray_angle, xplayer, yplayer, vert_vals);
	if (distance_horz == 0 || distance_vert == 0)
	{
		if (distance_horz == 0)
		{
			line(vars, xplayer, yplayer, vert_vals[0], vert_vals[1]);
			return ;
		}
		else if (distance_vert == 0)
		{
			line(vars, xplayer, yplayer, horz_vals[0], horz_vals[1]);
			return ;
		}
	}
	if (distance_horz > distance_vert)
	{
		line(vars, xplayer, yplayer, vert_vals[0], vert_vals[1]);
	}
	else
	{
		line(vars, xplayer, yplayer, horz_vals[0], horz_vals[1]);
	}
	return ;
}

void	render_rays(t_vars *vars)
{
	int		i;
	int		x_window;
	int		y_window;
	float	ray_angle;
	float	d_angle;

	i = 0;
	x_window = vars->player.x * 50 + (TILE_SIZE / 2);
	y_window = vars->player.y * 50 + (TILE_SIZE / 2);
	ray_angle = vars->player.rotation_angle - (((float)FOV / (float)180 * PI) / 2);
	d_angle = (((float)FOV / (float)180) * PI) / WINDOW_WIDTH;
	while (i < WINDOW_WIDTH)
	{
		// render ray
		render_ray(vars, ray_angle, x_window, y_window);
		ray_angle += d_angle;
		i++;
	}
}
