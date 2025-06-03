/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/03 00:00:00 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_line(char *line, char *invalid_char, int *pos)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
			line[i] != 'W')
		{
			*invalid_char = line[i];
			*pos = i;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_boundary_cell(char **map, int i, int j,
								int height, int width)
{
	if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
		return (0);
	if (map[i - 1][j] == ' ' || map[i - 1][j] == '*' ||
		map[i + 1][j] == ' ' || map[i + 1][j] == '*' ||
		map[i][j - 1] == ' ' || map[i][j - 1] == '*' ||
		map[i][j + 1] == ' ' || map[i][j + 1] == '*')
		return (0);
	return (1);
}

int	is_map_enclosed(char **map, int height, int width, int error_pos[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!check_boundary_cell(map, i, j, height, width))
				{
					error_pos[0] = j;
					error_pos[1] = i;
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_player_position(char **map, int height,
								int width, int *player_count)
{
	int	i;
	int	j;

	*player_count = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
				(*player_count)++;
			j++;
		}
		i++;
	}
	return (*player_count == 1);
}
