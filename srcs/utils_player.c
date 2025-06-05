/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 05:03:35 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_rotation_angle(char c)
{
	if (c == 'E')
		return (0);
	else if (c == 'N')
		return (PI / 2);
	else if (c == 'W')
		return (PI);
	else
		return ((PI * 3) / 2);
}

void	get_pos_p(t_vars *vars)
{
	vars->player.y = 0;
	while (vars->map[vars->player.y])
	{
		vars->player.x = 0;
		while (*((vars->map[vars->player.y]) + vars->player.x))
		{
			if (check_player(vars->map[vars->player.y][vars->player.x]))
			{
				vars->player.ort = vars->map[vars->player.y][vars->player.x];
				vars->player.rotation_angle
					= get_rotation_angle(
						vars->map[vars->player.y][vars->player.x]);
				return ;
			}
			(vars->player.x)++;
		}
		(vars->player.y)++;
	}
}

void	print_orientation(t_vars *vars)
{
	vars->player.rotation_angle = normalize_angle(vars->player.rotation_angle);
}
