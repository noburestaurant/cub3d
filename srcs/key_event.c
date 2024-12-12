/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:04:04 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/12 18:06:03 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_possible_to_move(t_vars *vars)
{
	return (vars->map[vars->player.y][vars->player.x] != '1');
}

void	update_map(t_vars *vars, int x_before, int y_before)
{
	vars->map[y_before][x_before] = '0';
	vars->map[vars->player.y][vars->player.x] = vars->player.ort;
	if (vars->move_count < INT_MAX)
		vars->move_count++;
	render_map(vars);
}

void	reset_player(t_vars *vars, int x_before, int y_before)
{
	vars->player.x = x_before;
	vars->player.y = y_before;
}

int	key_hook(int keycode, t_vars *vars)
{
	int	x_before;
	int	y_before;

	x_before = vars->player.x;
	y_before = vars->player.y;
	if (keycode == ESC)
		error_message_and_free(vars, "", 0);
	if (keycode == W || keycode == S || keycode == D || keycode == A)
	{
		if (keycode == W)
			vars->player.walk_direction = vars->player.rotation_angle;
		else if (keycode == S)
			vars->player.walk_direction = vars->player.rotation_angle + PI;
		else if (keycode == D)
			vars->player.walk_direction = vars->player.rotation_angle
				- (PI / 2);
		else if (keycode == A)
			vars->player.walk_direction = vars->player.rotation_angle
				+ (PI / 2);
		if (is_equal(vars->player.walk_direction, 0))
			vars->player.x++;
		else if (is_equal(vars->player.walk_direction, (PI / 2)))
			vars->player.y--;
		else if (is_equal(vars->player.walk_direction, PI))
			vars->player.x--;
		else if (is_equal(vars->player.walk_direction, (PI * 3 / 2)))
			vars->player.y++;
	}
	else if (keycode == RIGHT)
		vars->player.rotation_angle -= (PI / 2);
	else if (keycode == LEFT)
		vars->player.rotation_angle += (PI / 2);
	if (check_possible_to_move(vars))
		update_map(vars, x_before, y_before);
	else
		reset_player(vars, x_before, y_before);
	return (0);
}

int	window_close(t_vars *vars)
{
	error_message_and_free(vars, "", 0);
	return (1);
}
