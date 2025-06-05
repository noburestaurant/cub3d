/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_horizontal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 13:17:20 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_with_params(t_vars *vars, t_ray_calc *calc)
{
	t_line_params	params;

	params = (t_line_params){calc->xplayer, calc->yplayer,
		calc->vals[0], calc->vals[1]};
	line(vars, params);
}

void	handle_missing_distance(t_vars *vars, float distance_horz,
		float distance_vert, t_ray_calc calc[2])
{
	if (distance_horz == 0)
		draw_line_with_params(vars, &calc[1]);
	else if (distance_vert == 0)
		draw_line_with_params(vars, &calc[0]);
}

static void	init_horizontal_calc(t_ray_calc *calc, float *xstep, float *ystep)
{
	float	xintercept;
	float	yintercept;

	yintercept = (calc->yplayer / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(calc->ray_angle))
		yintercept += TILE_SIZE;
	xintercept = calc->xplayer + ((calc->yplayer - yintercept)
			/ tan(calc->ray_angle));
	*ystep = TILE_SIZE;
	if (is_ray_facing_up(calc->ray_angle))
		*ystep *= -1;
	*xstep = *ystep / tan(calc->ray_angle);
	if (is_ray_facing_left(calc->ray_angle) && *xstep > 0)
		*xstep *= -1;
	if (is_ray_facing_right(calc->ray_angle) && *xstep < 0)
		*xstep *= -1;
	calc->vals[0] = xintercept;
	calc->vals[1] = yintercept;
}

static int	check_horizontal_wall(t_vars *vars, t_ray_calc *calc)
{
	int	check_x;
	int	check_y;

	check_x = calc->vals[0];
	check_y = calc->vals[1] - (is_ray_facing_up(calc->ray_angle));
	return (has_wall_at(vars, check_x, check_y));
}

float	calculate_wall_hit_distance_horizontal_delete(t_vars *vars,
		t_ray_calc *calc)
{
	float	xstep;
	float	ystep;
	int		wall_hit_x;
	int		wall_hit_y;

	init_horizontal_calc(calc, &xstep, &ystep);
	wall_hit_x = 0;
	wall_hit_y = 0;
	while (is_in_bounds(calc))
	{
		if (check_horizontal_wall(vars, calc))
		{
			wall_hit_x = calc->vals[0];
			wall_hit_y = calc->vals[1] - (is_ray_facing_up(calc->ray_angle));
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
