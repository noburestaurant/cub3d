/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:29:17 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:10:43 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_config_value(char *line, int type)
{
	char	*value;

	if (type <= 3)
		value = ft_strtrim(line + 3, " \t\n\r\v\f");
	else
		value = ft_strtrim(line + 2, " \t\n\r\v\f");
	return (value);
}

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

int	process_config_by_type(t_config *config, int type,
		char *value, char **error_msg)
{
	if (type == 0)
		return (handle_no_config(config, value, error_msg));
	else if (type == 1)
		return (handle_so_config(config, value, error_msg));
	else if (type == 2)
		return (handle_we_config(config, value, error_msg));
	else if (type == 3)
		return (handle_ea_config(config, value, error_msg));
	else if (type == 4)
		return (handle_floor_config(config, value, error_msg));
	else if (type == 5)
		return (handle_ceil_config(config, value, error_msg));
	return (-1);
}

int	parse_config_line(char *line, t_config *config, char **error_msg)
{
	int		type;
	char	*value;

	type = get_identifier_type(line);
	if (type == -1)
		return (0);
	value = get_config_value(line, type);
	if (!value)
	{
		*error_msg = ft_strdup("Memory allocation failed");
		return (-1);
	}
	return (process_config_by_type(config, type, value, error_msg));
}

void	process_not_map_line(t_vars *vars, char *line, t_parse_data *data,
		int fd)
{
	if (parse_config_line(line, &vars->config, &data->error_msg) == 0)
	{
		start_map_section(line, data, vars);
		data->in_map_section = 1;
	}
	else if (data->error_msg)
		handle_config_error(line, fd, vars, data->error_msg);
}
