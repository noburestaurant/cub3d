/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/03 14:00:00 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_texture_config(int type, char *value, t_config *config,
	char **error_msg)
{
	if (type == 0)
	{
		if (config->has_no)
		{
			*error_msg = ft_strdup("Duplicate identifier");
			return (-1);
		}
		if (!is_valid_texture_path(value, error_msg))
			return (-1);
		config->no_path = value;
		config->has_no = 1;
	}
	else if (type == 1)
	{
		if (config->has_so)
		{
			*error_msg = ft_strdup("Duplicate identifier");
			return (-1);
		}
		if (!is_valid_texture_path(value, error_msg))
			return (-1);
		config->so_path = value;
		config->has_so = 1;
	}
	return (1);
}

static int	handle_texture_config2(int type, char *value, t_config *config,
	char **error_msg)
{
	if (type == 2)
	{
		if (config->has_we)
		{
			*error_msg = ft_strdup("Duplicate identifier");
			return (-1);
		}
		if (!is_valid_texture_path(value, error_msg))
			return (-1);
		config->we_path = value;
		config->has_we = 1;
	}
	else if (type == 3)
	{
		if (config->has_ea)
		{
			*error_msg = ft_strdup("Duplicate identifier");
			return (-1);
		}
		if (!is_valid_texture_path(value, error_msg))
			return (-1);
		config->ea_path = value;
		config->has_ea = 1;
	}
	return (1);
}

static int	handle_color_config(int type, char *value, t_config *config,
	char **error_msg)
{
	if (type == 4)
	{
		if (config->has_floor)
		{
			*error_msg = ft_strdup("Duplicate identifier");
			return (-1);
		}
		if (!is_valid_color_format(value, config->floor_color, error_msg))
			return (-1);
		config->has_floor = 1;
	}
	else if (type == 5)
	{
		if (config->has_ceil)
		{
			*error_msg = ft_strdup("Duplicate identifier");
			return (-1);
		}
		if (!is_valid_color_format(value, config->ceil_color, error_msg))
			return (-1);
		config->has_ceil = 1;
	}
	return (1);
}

// 設定項目の解析処理
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
	if (type <= 1)
		result = handle_texture_config(type, value, config, error_msg);
	else if (type <= 3)
		result = handle_texture_config2(type, value, config, error_msg);
	else
		result = handle_color_config(type, value, config, error_msg);
	if (result == -1)
		free(value);
	if (type >= 4)
		free(value);
	return (result);
}

int	validate_config(t_config *config, char **error_msg)
{
	if (!config->has_no || !config->has_so
		|| !config->has_we || !config->has_ea
		|| !config->has_floor || !config->has_ceil)
	{
		*error_msg = ft_strdup("Missing required configuration elements");
		return (0);
	}
	return (1);
}
