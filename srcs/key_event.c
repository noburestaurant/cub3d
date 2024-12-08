/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:04:04 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/08 16:24:08 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_possible_to_move(t_vars *vars)
{
	return (vars->map[vars->player.y][vars->player.x] != '1');
}

void	update_map(t_vars *vars, int x_before, int y_before)
{
	if (x_before == vars->player.x && y_before == vars->player.y)
		return ;
	vars->map[vars->player.y][vars->player.x] = vars->player.ort;
	vars->map[y_before][x_before] = '0';
	if (vars->move_count <= INT_MAX)
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
	else if (keycode == W || keycode == 65362)
		vars->player.y--;
	else if (keycode == S || keycode == 65364)
		vars->player.y++;
	else if (keycode == D || keycode == 65363)
		vars->player.x++;
	else if (keycode == A || keycode == 65361)
		vars->player.x--;
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
