/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/03 14:00:00 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// マップの一行が有効かチェック
int	is_valid_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' &&
			line[i] != 'N' && line[i] != 'S' &&
			line[i] != 'E' && line[i] != 'W')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// マップデータを調整（各行の長さを最大幅に合わせて'*'で埋める）
int	adjust_map_data(t_config *config, char **error_msg)
{
	(void)config;
	(void)error_msg;
	return (1);
}

// マップが壁で完全に囲まれているかチェック
int	is_map_enclosed(char **map, char **error_msg)
{
	int	i;
	int	j;
	int	height;
	int	width;

	if (!map || !map[0])
	{
		*error_msg = ft_strdup("Invalid map");
		return (0);
	}
	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width && map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' ||
				map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1 ||
					(map[i - 1] && map[i - 1][j] == ' ') ||
					(map[i + 1] && map[i + 1][j] == ' ') ||
					map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
				{
					*error_msg = ft_strdup("Map is not surrounded by walls");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	read_map_section(int fd, t_config *config, char **error_msg)
{
	char	*line;

	(void)config;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
	}
	*error_msg = NULL;
	return (1);
}
