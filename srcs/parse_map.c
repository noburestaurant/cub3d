/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:44:12 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 13:49:58 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_first_map_line(t_vars *vars, char *line,
		t_parse_data *data)
{
	if (is_valid_map_line(line))
	{
		data->raw_map[data->height] = ft_strdup(line);
		if (ft_strlen(line) > (size_t)data->max_width)
			data->max_width = ft_strlen(line);
		data->height++;
	}
	else
		error_message_and_free(vars, "Invalid character in map", 1);
}

void	start_map_section(char *line, t_parse_data *data, t_vars *vars)
{
	if (!validate_all_configs(vars))
		error_message_and_free(vars, "Missing required element", 1);
	data->raw_map = allocate_raw_map();
	if (!data->raw_map)
		error_message_and_free(vars, "Memory allocation failed", 1);
	process_first_map_line(vars, line, data);
}

void	handle_map_line(char *line, t_parse_data *data)
{
	if (ft_strlen(line) > 0)
	{
		data->raw_map[data->height] = ft_strdup(line);
		if (ft_strlen(line) > (size_t)data->max_width)
			data->max_width = ft_strlen(line);
		data->height++;
	}
}

void	process_map_line(t_vars *vars, char *line, t_parse_data *data)
{
	if (ft_strlen(line) == 0 || is_valid_map_line(line))
	{
		if (ft_strlen(line) == 0 && data->height > 0)
			error_message_and_free(vars,
				"Map should not have an empty line", 1);
		if (ft_strlen(line) > 0)
			handle_map_line(line, data);
	}
	else
		error_message_and_free(vars, "Invalid character in map", 1);
}
