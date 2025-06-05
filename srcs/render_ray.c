/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:10 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 13:17:20 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_calc(t_ray_calc *calc, float ray_angle,
		int xplayer, int yplayer)
{
	calc->ray_angle = ray_angle;
	calc->xplayer = xplayer;
	calc->yplayer = yplayer;
	calc->vals[0] = 0;
	calc->vals[1] = 0;
}

static void	draw_shorter_ray(t_vars *vars, float distance_horz,
		float distance_vert, t_ray_calc calc[2])
{
	if (distance_horz == 0 || distance_vert == 0)
	{
		handle_missing_distance(vars, distance_horz, distance_vert, calc);
		return ;
	}
	if (distance_horz > distance_vert)
		draw_line_with_params(vars, &calc[1]);
	else
		draw_line_with_params(vars, &calc[0]);
}

void	render_ray(t_vars *vars, float ray_angle, int xplayer, int yplayer)
{
	float		distance_horz;
	float		distance_vert;
	t_ray_calc	calc[2];

	init_ray_calc(&calc[0], ray_angle, xplayer, yplayer);
	init_ray_calc(&calc[1], ray_angle, xplayer, yplayer);
	distance_horz = calculate_wall_hit_distance_horizontal_delete(vars,
			&calc[0]);
	distance_vert = calculate_wall_hit_distance_vertical_delete(vars,
			&calc[1]);
	draw_shorter_ray(vars, distance_horz, distance_vert, calc);
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
	ray_angle = vars->player.rotation_angle
		- (((float)FOV / (float)180 * PI) / 2);
	d_angle = (((float)FOV / (float)180) * PI) / WINDOW_WIDTH;
	while (i < WINDOW_WIDTH)
	{
		render_ray(vars, ray_angle, x_window, y_window);
		ray_angle += d_angle;
		i++;
	}
}
