/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_finalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:29:19 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:22:14 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**alloc_two_dimensional_array(int height, int width)
{
	char	**arrays;
	int		i;

	i = 0;
	arrays = (char **)malloc(sizeof(char *) * (height + 1));
	if (!arrays)
		return (NULL);
	i = 0;
	while (i < height)
	{
		arrays[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!arrays[i])
		{
			while (--i >= 0)
				free(arrays[i]);
			free(arrays);
			return (NULL);
		}
		arrays[i][width] = '\0';
		i++;
	}
	arrays[height] = NULL;
	return (arrays);
}

char	**adjust_map_data(char **raw_map, int height, int width)
{
	char	**adjusted_map;
	int		i;
	int		j;
	int		len;

	adjusted_map = alloc_two_dimensional_array(height, width);
	if (!adjusted_map)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		j = -1;
		len = ft_strlen(raw_map[i]);
		while (++j < len)
		{
			if (raw_map[i][j] != ' ')
				adjusted_map[i][j] = raw_map[i][j];
			else
				adjusted_map[i][j] = '*';
		}
		while (++j < width)
			adjusted_map[i][j] = '*';
	}
	return (adjusted_map);
}

void	cleanup_raw_map(char **raw_map, int height)
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

void	validate_final_map(t_vars *vars, t_parse_data *data)
{
	int	player_count;

	player_count = 0;
	if (!validate_player_position(vars->map, data->height,
			data->max_width, &player_count))
	{
		if (player_count == 0)
			error_message_and_free(vars, "No player starting position", 1);
		else
			error_message_and_free(vars,
				"Multiple player starting positions", 1);
	}
	if (!is_map_enclosed(vars->map, data->height, data->max_width))
		error_message_and_free(vars, "Map is not surrounded by walls", 1);
}

void	finalize_parsing(t_vars *vars, t_parse_data *data)
{
	if (data->height == 0)
		error_message_and_free(vars, "Missing required element", 1);
	data->raw_map[data->height] = NULL;
	vars->map = adjust_map_data(data->raw_map, data->height, data->max_width);
	cleanup_raw_map(data->raw_map, data->height);
	if (!vars->map)
		error_message_and_free(vars, "Momory allocation failed", 1);
	validate_final_map(vars, data);
	vars->height = data->height;
	vars->width = data->max_width;
}
