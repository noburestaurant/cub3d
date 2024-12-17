/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_field_of_view_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:55:59 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 07:56:36 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_render_info(t_vars *vars, float projected_wall_height)
{
	vars->render_info.texture_x = 0;
	vars->render_info.texture_y = 0;
	vars->render_info.texture_height = TILE_SIZE;
	vars->render_info.wall_direction = 0;
	vars->render_info.start_y = (WINDOW_HEIGHT / 2)
		- (projected_wall_height / 2);
}
