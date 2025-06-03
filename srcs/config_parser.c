/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/03 00:00:00 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_identifier_type(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (-1);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (0);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (1);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (2);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (3);
	else if (line[0] == 'F' && line[1] == ' ')
		return (4);
	else if (line[0] == 'C' && line[1] == ' ')
		return (5);
	return (-1);
}

static int	parse_texture_config(int type, char *value,
								t_config *config, char **error_msg)
{
	if (type == 0 && !config->has_no)
	{
		if (!is_valid_texture_path(value, error_msg))
			return (-1);
		config->no_path = value;
		config->has_no = 1;
	}
	else if (type == 1 && !config->has_so)
	{
		if (!is_valid_texture_path(value, error_msg))
			return (-1);
		config->so_path = value;
		config->has_so = 1;
	}
	else if (type == 2 && !config->has_we)
	{
		if (!is_valid_texture_path(value, error_msg))
			return (-1);
		config->we_path = value;
		config->has_we = 1;
	}
	else if (type == 3 && !config->has_ea)
	{
		if (!is_valid_texture_path(value, error_msg))
			return (-1);
		config->ea_path = value;
		config->has_ea = 1;
	}
	else
	{
		*error_msg = ft_strdup("Duplicate identifier");
		return (-1);
	}
	return (1);
}

static int	parse_color_config(int type, char *value,
								t_config *config, char **error_msg)
{
	if (type == 4 && !config->has_floor)
	{
		if (!is_valid_color_format(value, config->floor_color, error_msg))
			return (-1);
		config->has_floor = 1;
	}
	else if (type == 5 && !config->has_ceil)
	{
		if (!is_valid_color_format(value, config->ceil_color, error_msg))
			return (-1);
		config->has_ceil = 1;
	}
	else
	{
		*error_msg = ft_strdup("Duplicate identifier");
		return (-1);
	}
	return (1);
}

int	parse_config_line(char *line, t_config *config, char **error_msg)
{
	int		type;
	char	*value;
	int		result;

	type = get_identifier_type(line);
	if (type == -1)
		return (0);
	if (type <= 3)
		value = ft_strtrim(line + 3, " \t\n\r\v\f");
	else
		value = ft_strtrim(line + 2, " \t\n\r\v\f");
	if (!value)
		return (-1);
	if (type <= 3)
		result = parse_texture_config(type, value, config, error_msg);
	else
	{
		result = parse_color_config(type, value, config, error_msg);
		free(value);
	}
	if (result == -1)
		free(value);
	return (result);
}
