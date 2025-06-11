/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:44:05 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 13:44:30 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_file_content(int fd, t_vars *vars, t_parse_data *data)
{
	char	*line;

	data->in_map_section = 0;
	data->height = 0;
	data->max_width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
			handle_empty_line(line, data->in_map_section, vars);
		else
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			if (!data->in_map_section)
				process_not_map_line(vars, line, data, fd);
			else
				process_map_line(vars, line, data);
			free(line);
		}
		line = get_next_line(fd);
	}
}
