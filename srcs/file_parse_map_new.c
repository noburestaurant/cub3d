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

int	is_valid_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	adjust_map_data(t_config *config, char **error_msg)
{
	(void)config;
	(void)error_msg;
	return (1);
}

int	read_map_section(int fd, t_config *config, char **error_msg)
{
	char	*line;

	(void)config;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	*error_msg = NULL;
	return (1);
}
