/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:34 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/08 16:29:44 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_valid_path(t_vars *vars)
{
	char	**duplicated_map;

	duplicated_map = duplicate_map(vars);
	if (duplicated_map == NULL)
		error_message_and_free(vars, "Unexpected Error\n", 1);
	flood_fill(vars, duplicated_map, vars->player.x, vars->player.y);
	check_no_c_in_map(duplicated_map, vars);
}

int	flood_fill(t_vars *vars, char **map, int col, int row)
{
	if (row < 0 || col < 0 || vars->height <= row || vars->width <= col)
		return (1);
	if (map[row][col] != '0' && check_player(map[row][col]))
	{
		return (1);
	}
	map[row][col] = '*';
	flood_fill(vars, map, col, row + 1);
	flood_fill(vars, map, col, row - 1);
	flood_fill(vars, map, col + 1, row);
	flood_fill(vars, map, col - 1, row);
	return (0);
}

void	check_no_c_in_map(char **duplicated_map, t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (duplicated_map[i][j] == 'C')
			{
				free_map(duplicated_map);
				error_message_and_free(vars, "Invalid map\n", 1);
			}
			j++;
		}
		i++;
	}
	free_map(duplicated_map);
}
