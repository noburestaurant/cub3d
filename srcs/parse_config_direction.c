/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_direction.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:29:08 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:19:03 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_texture_config(char *value, char **path, char **error_msg)
{
	if (!is_valid_texture_path(value, error_msg))
	{
		free(value);
		return (-1);
	}
	*path = value;
	return (1);
}

int	handle_no_config(t_config *config, char *value, char **error_msg)
{
	if (handle_duplicate_config(config->has_no, error_msg, value) == -1)
		return (-1);
	if (process_texture_config(value, &config->no_path, error_msg) == -1)
		return (-1);
	config->has_no = 1;
	return (1);
}

int	handle_so_config(t_config *config, char *value, char **error_msg)
{
	if (handle_duplicate_config(config->has_so, error_msg, value) == -1)
		return (-1);
	if (process_texture_config(value, &config->so_path, error_msg) == -1)
		return (-1);
	config->has_so = 1;
	return (1);
}

int	handle_we_config(t_config *config, char *value, char **error_msg)
{
	if (handle_duplicate_config(config->has_we, error_msg, value) == -1)
		return (-1);
	if (process_texture_config(value, &config->we_path, error_msg) == -1)
		return (-1);
	config->has_we = 1;
	return (1);
}

int	handle_ea_config(t_config *config, char *value, char **error_msg)
{
	if (handle_duplicate_config(config->has_ea, error_msg, value) == -1)
		return (-1);
	if (process_texture_config(value, &config->ea_path, error_msg) == -1)
		return (-1);
	config->has_ea = 1;
	return (1);
}
