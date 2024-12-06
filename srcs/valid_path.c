/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:34 by hnakayam          #+#    #+#             */
/*   Updated: 2024/08/29 20:21:43 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	check_valid_path(t_vars *vars)
{
	char	**duplicated_map;

	duplicated_map = duplicate_map(vars);
	if (duplicated_map == NULL)
		error_message_and_free(vars, "Unexpected Error\n", 1);
	flood_fill(vars, duplicated_map, vars->x_p, vars->y_p);
	check_no_c_in_map(duplicated_map, vars);
}

int	flood_fill(t_vars *vars, char **map, int col, int row)
{
	if (row < 0 || col < 0 || vars->height <= row || vars->width <= col)
		return (1);
	if (map[row][col] == 'E')
	{
		vars->enable = 1;
		return (1);
	}
	if (map[row][col] != '0' && map[row][col] != 'P' && map[row][col] != 'C')
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
