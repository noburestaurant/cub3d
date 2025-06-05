/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 04:27:56 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_file(char *filename, char **error_msg)
{
	int	fd;

	if (!is_valid_extension(filename))
	{
		*error_msg = ft_strdup("File must have .cub extension");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		*error_msg = ft_strdup("Cannot open file");
		return (-1);
	}
	return (fd);
}

static int	process_config_line(char *line, t_config *config,
		char **error_msg)
{
	char	*trimmed_line;
	int		result;

	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (!trimmed_line)
		return (0);
	if (ft_strlen(trimmed_line) == 0 || trimmed_line[0] == '#')
	{
		free(trimmed_line);
		return (1);
	}
	result = parse_config_line(trimmed_line, config, error_msg);
	free(trimmed_line);
	return (result);
}

static int	read_config_section(int fd, t_config *config, char **error_msg)
{
	char	*line;
	int		result;

	line = get_next_line(fd);
	while (line != NULL)
	{
		result = process_config_line(line, config, error_msg);
		free(line);
		if (result == 0)
			return (0);
		if (result == 2)
			break ;
		line = get_next_line(fd);
	}
	return (validate_config(config, error_msg));
}

static int	parse_file_content(int fd, t_config *config, char **error_msg)
{
	if (!read_config_section(fd, config, error_msg))
		return (0);
	if (!read_map_section(fd, config, error_msg))
		return (0);
	if (!validate_player_position(config, error_msg))
		return (0);
	return (1);
}

int	parse_file(char *filename, t_config *config, char **error_msg)
{
	int	fd;
	int	result;

	init_config(config);
	fd = open_file(filename, error_msg);
	if (fd == -1)
		return (0);
	result = parse_file_content(fd, config, error_msg);
	close(fd);
	if (!result)
		cleanup_config(config);
	return (result);
}
