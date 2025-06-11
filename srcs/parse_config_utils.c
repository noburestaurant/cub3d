/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:29:12 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:20:06 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_config_error(char *line, int fd, t_vars *vars,
		char *error_msg)
{
	free(line);
	close(fd);
	error_message_and_free(vars, error_msg, 1);
}

void	initialize_config(t_vars *vars)
{
	vars->config.has_no = 0;
	vars->config.has_so = 0;
	vars->config.has_we = 0;
	vars->config.has_ea = 0;
	vars->config.has_floor = 0;
	vars->config.has_ceil = 0;
	vars->config.no_path = NULL;
	vars->config.so_path = NULL;
	vars->config.we_path = NULL;
	vars->config.ea_path = NULL;
}

int	handle_duplicate_config(int has_config, char **error_msg, char *value)
{
	if (has_config)
	{
		*error_msg = ft_strdup("Duplicate identifier");
		free(value);
		return (-1);
	}
	return (0);
}
