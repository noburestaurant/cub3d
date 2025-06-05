/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 05:03:35 by hnakayam         ###   ########.fr       */
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
