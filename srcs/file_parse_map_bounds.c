/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_map_bounds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 04:46:41 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_or_empty(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_map_boundaries(t_map_info *info, int i, int j)
{
	if (i == 0 || i == info->height - 1 || j == 0 || j == info->width - 1
		|| (info->map[i - 1] && info->map[i - 1][j] == ' ')
		|| (info->map[i + 1] && info->map[i + 1][j] == ' ')
		|| info->map[i][j - 1] == ' ' || info->map[i][j + 1] == ' ')
		return (0);
	return (1);
}

static int	validate_map_position(t_map_info *info, int i, int j)
{
	if (is_player_or_empty(info->map[i][j]))
	{
		if (!check_map_boundaries(info, i, j))
			return (0);
	}
	return (1);
}

static int	check_map_rows(t_map_info *info, char **error_msg)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->height)
	{
		j = 0;
		while (j < info->width && info->map[i][j])
		{
			if (!validate_map_position(info, i, j))
			{
				*error_msg = ft_strdup("Map is not surrounded by walls");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	is_map_enclosed(char **map, char **error_msg)
{
	t_map_info	info;

	if (!map || !map[0])
	{
		*error_msg = ft_strdup("Invalid map");
		return (0);
	}
	info.map = map;
	info.height = 0;
	while (map[info.height])
		info.height++;
	info.width = ft_strlen(map[0]);
	return (check_map_rows(&info, error_msg));
}
