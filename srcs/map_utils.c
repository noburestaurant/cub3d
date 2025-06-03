/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/03 00:00:00 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**allocate_map_memory(int height, int width)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

static void	copy_and_fill_line(char *dest, char *src, int width)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(src);
	while (j < len)
	{
		dest[j] = src[j];
		j++;
	}
	while (j < width)
	{
		dest[j] = '*';
		j++;
	}
	dest[width] = '\0';
}

char	**adjust_map_data(char **raw_map, int height, int width)
{
	char	**adjusted_map;
	int		i;

	adjusted_map = allocate_map_memory(height, width);
	if (!adjusted_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy_and_fill_line(adjusted_map[i], raw_map[i], width);
		i++;
	}
	adjusted_map[height] = NULL;
	return (adjusted_map);
}

void	free_raw_map(char **raw_map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(raw_map[i]);
		i++;
	}
	free(raw_map);
}
