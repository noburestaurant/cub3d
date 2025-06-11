/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:29:02 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:35:47 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_color_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

int	is_valid_color_format(char *color_str, int color[3],
		char **error_msg)
{
	char	**parts;
	int		i;

	parts = ft_split(color_str, ',');
	if (!parts)
		return (0);
	if (!validate_color_count(parts, error_msg))
	{
		free_color_parts(parts);
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		if (!validate_color_value(parts[i], &color[i], error_msg))
		{
			free_color_parts(parts);
			return (0);
		}
		i++;
	}
	free_color_parts(parts);
	return (1);
}

int	process_color_config(char *value, int *color, char **error_msg)
{
	if (!is_valid_color_format(value, color, error_msg))
	{
		free(value);
		return (-1);
	}
	free(value);
	return (1);
}

int	handle_floor_config(t_config *config, char *value, char **error_msg)
{
	if (handle_duplicate_config(config->has_floor, error_msg, value) == -1)
		return (-1);
	if (process_color_config(value, config->floor_color, error_msg) == -1)
		return (-1);
	config->has_floor = 1;
	return (1);
}

int	handle_ceil_config(t_config *config, char *value, char **error_msg)
{
	if (handle_duplicate_config(config->has_ceil, error_msg, value) == -1)
		return (-1);
	if (process_color_config(value, config->ceil_color, error_msg) == -1)
		return (-1);
	config->has_ceil = 1;
	return (1);
}
