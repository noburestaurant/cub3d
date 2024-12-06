/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:04:04 by hnakayam          #+#    #+#             */
/*   Updated: 2024/08/29 20:21:43 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_possible_to_move(t_vars *vars)
{
	if (vars->map[vars->y_p][vars->x_p] == 'E')
	{
		if (vars->c == 0)
		{
			ft_printf("Success!\n");
			error_message_and_free(vars, "", 0);
		}
		else
			return (0);
	}
	else if (vars->map[vars->y_p][vars->x_p] != '1')
		return (1);
	return (0);
}

void	update_map(t_vars *vars, int x_before, int y_before)
{
	if (x_before == vars->x_p && y_before == vars->y_p)
		return ;
	if (vars->map[vars->y_p][vars->x_p] == 'C')
		(vars->c)--;
	vars->map[vars->y_p][vars->x_p] = 'P';
	vars->map[y_before][x_before] = '0';
	if (vars->move_count <= INT_MAX)
		vars->move_count++;
	render_map(vars);
}

void	reset_player(t_vars *vars, int x_before, int y_before)
{
	vars->x_p = x_before;
	vars->y_p = y_before;
}

int	key_hook(int keycode, t_vars *vars)
{
	int	x_before;
	int	y_before;

	x_before = vars->x_p;
	y_before = vars->y_p;
	if (keycode == ESC)
		error_message_and_free(vars, "", 0);
	else if (keycode == W || keycode == 65362)
		vars->y_p--;
	else if (keycode == S || keycode == 65364)
		vars->y_p++;
	else if (keycode == D || keycode == 65363)
		vars->x_p++;
	else if (keycode == A || keycode == 65361)
		vars->x_p--;
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
