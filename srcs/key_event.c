/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:04:04 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 13:42:00 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_possible_to_move(t_vars *vars)
{
	return (vars->map[vars->player.y][vars->player.x] != '1');
}

void	reset_player(t_vars *vars, int x_before, int y_before)
{
	vars->player.x = x_before;
	vars->player.y = y_before;
}

void	handle_movement_keys(int keycode, t_vars *vars)
{
	if (keycode == W)
		vars->player.walk_direction = vars->player.rotation_angle;
	else if (keycode == S)
		vars->player.walk_direction = vars->player.rotation_angle + PI;
	else if (keycode == D)
		vars->player.walk_direction = vars->player.rotation_angle - (PI / 2);
	else if (keycode == A)
		vars->player.walk_direction = vars->player.rotation_angle + (PI / 2);
}

void	update_player_position(t_vars *vars)
{
	double	normalized_angle;

	normalized_angle = normalize_angle(vars->player.walk_direction);
	if (is_equal(normalized_angle, 0))
		vars->player.x++;
	else if (is_equal(normalized_angle, (PI / 2)))
		vars->player.y--;
	else if (is_equal(normalized_angle, PI))
		vars->player.x--;
	else if (is_equal(normalized_angle, (PI * 3 / 2)))
		vars->player.y++;
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
		handle_movement_keys(keycode, vars);
		update_player_position(vars);
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
