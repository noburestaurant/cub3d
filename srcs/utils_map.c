/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 14:11:07 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	measure(t_vars *vars)
{
	vars->width = 0;
	vars->height = 0;
	while (vars->map[vars->height])
		(vars->height)++;
	while (vars->map[0][vars->width])
		(vars->width)++;
}

int	has_wall_at(t_vars *vars, int next_horizontal_touch_x,
	int next_horizontal_touch_y)
{
	int	coordinate_x_in_map;
	int	coordinate_y_in_map;

	coordinate_x_in_map = next_horizontal_touch_x / TILE_SIZE;
	coordinate_y_in_map = next_horizontal_touch_y / TILE_SIZE;
	return (vars->map[coordinate_y_in_map][coordinate_x_in_map] == '1');
}

char	**duplicate_map(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) * (vars->height + 1));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < vars->height)
	{
		map[i] = (char *)malloc(sizeof(char ) * (vars->width + 1));
		if (map[i] == NULL)
			return (NULL);
		j = 0;
		while (j < vars->width)
		{
			map[i][j] = vars->map[i][j];
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}
