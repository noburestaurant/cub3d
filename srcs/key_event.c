/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:04:04 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/08 18:58:13 by retanaka         ###   ########.fr       */
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
	else if (keycode == W)
		vars->player.y--;
	else if (keycode == S)
		vars->player.y++;
	else if (keycode == D)
		vars->player.x++;
	else if (keycode == A)
		vars->player.x--;
	else if (keycode == RIGHT)
	{
		if (vars->player.ort == 'N')
			vars->player.ort = 'E';
		else if (vars->player.ort == 'E')
			vars->player.ort = 'S';
		else if (vars->player.ort == 'S')
			vars->player.ort = 'W';
		else if (vars->player.ort == 'W')
			vars->player.ort = 'N';
		if (vars->player.ort == 'N')
			vars->img_player.current = vars->img_player.n;
		else if (vars->player.ort == 'E')
			vars->img_player.current = vars->img_player.e;
		else if (vars->player.ort == 'S')
			vars->img_player.current = vars->img_player.s;
		else if (vars->player.ort == 'W')
			vars->img_player.current = vars->img_player.w;
		update_map(vars, x_before, y_before);
	}
	else if (keycode == LEFT)
	{
		if (vars->player.ort == 'N')
			vars->player.ort = 'W';
		else if (vars->player.ort == 'E')
			vars->player.ort = 'N';
		else if (vars->player.ort == 'S')
			vars->player.ort = 'E';
		else if (vars->player.ort == 'W')
			vars->player.ort = 'S';
		if (vars->player.ort == 'N')
			vars->img_player.current = vars->img_player.n;
		else if (vars->player.ort == 'E')
			vars->img_player.current = vars->img_player.e;
		else if (vars->player.ort == 'S')
			vars->img_player.current = vars->img_player.s;
		else if (vars->player.ort == 'W')
			vars->img_player.current = vars->img_player.w;
		update_map(vars, x_before, y_before);
	}
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
