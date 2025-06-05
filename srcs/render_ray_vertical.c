/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 05:20:14 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vertical_calc(t_ray_calc *calc, float *xstep, float *ystep)
{
	float	xintercept;
	float	yintercept;

	xintercept = calc->xplayer / TILE_SIZE * TILE_SIZE;
	if (is_ray_facing_right(calc->ray_angle))
		xintercept += TILE_SIZE;
	yintercept = calc->yplayer - ((xintercept - calc->xplayer)
			* tan(calc->ray_angle));
	*xstep = TILE_SIZE;
	if (is_ray_facing_left(calc->ray_angle) && *xstep > 0)
		*xstep *= -1;
	*ystep = *xstep * tan(calc->ray_angle);
	if (is_ray_facing_up(calc->ray_angle) && *ystep > 0)
		*ystep *= -1;
	if (is_ray_facing_down(calc->ray_angle) && *ystep < 0)
		*ystep *= -1;
	calc->vals[0] = xintercept;
	calc->vals[1] = yintercept;
}

static int	check_vertical_wall(t_vars *vars, t_ray_calc *calc)
{
	int	check_x;
	int	check_y;

	check_x = calc->vals[0] - (is_ray_facing_left(calc->ray_angle));
	check_y = calc->vals[1];
	return (has_wall_at(vars, check_x, check_y));
}

static int	is_in_vertical_bounds(t_ray_calc *calc)
{
	return (0 <= calc->vals[0] && calc->vals[0] < WINDOW_WIDTH
		&& 0 <= calc->vals[1] && calc->vals[1] < WINDOW_HEIGHT);
}

float	calculate_wall_hit_distance_vertical_delete(t_vars *vars,
		t_ray_calc *calc)
{
	float	xstep;
	float	ystep;
	int		wall_hit_x;
	int		wall_hit_y;

	init_vertical_calc(calc, &xstep, &ystep);
	wall_hit_x = 0;
	wall_hit_y = 0;
	while (is_in_vertical_bounds(calc))
	{
		if (check_vertical_wall(vars, calc))
		{
			wall_hit_x = calc->vals[0] - (is_ray_facing_left(calc->ray_angle));
			wall_hit_y = calc->vals[1];
			calc->vals[0] = wall_hit_x;
			calc->vals[1] = wall_hit_y;
			break ;
		}
		calc->vals[0] += xstep;
		calc->vals[1] += ystep;
	}
	if (wall_hit_x == 0 && wall_hit_y == 0)
		return (0);
	return (calculate_distance_between_two_points(calc->xplayer,
			calc->yplayer, wall_hit_x, wall_hit_y));
}
