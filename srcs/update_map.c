/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:16:49 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 12:17:08 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_map(t_vars *vars, int x_before, int y_before)
{
	vars->map[y_before][x_before] = '0';
	vars->map[vars->player.y][vars->player.x] = vars->player.ort;
	if (vars->move_count < INT_MAX)
		vars->move_count++;
	mlx_clear_window(vars->mlx, vars->win);

	// render map, player position, and rays
	render_map(vars);
	print_player(vars);
	render_rays(vars);
	print_orientation(vars);
	render_field_of_view(vars);
	// 

	// // render ceiling
	// print_orientation(vars);
	// render_floor_and_ceiling(vars);
	// render_field_of_view(vars);
	// // 
}
