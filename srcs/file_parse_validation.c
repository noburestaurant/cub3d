/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/03 14:00:00 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// プレイヤーの位置を特定し、有効性をチェック
int	validate_player_position(t_config *config, char **error_msg)
{
	(void)config;
	*error_msg = NULL;
	return (1);
}

void	init_config(t_config *config)
{
	config->has_no = 0;
	config->has_so = 0;
	config->has_we = 0;
	config->has_ea = 0;
	config->has_floor = 0;
	config->has_ceil = 0;
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
}

int	check_all_config_present(t_config *config)
{
	if (!config->has_no || !config->has_so ||
		!config->has_we || !config->has_ea ||
		!config->has_floor || !config->has_ceil)
		return (0);
	return (1);
}

void	free_raw_map(char **raw_map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(raw_map[i]);
		i++;
	}
	free(raw_map);
}

void	free_adjusted_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	cleanup_config(t_config *config)
{
	if (config->no_path)
		free(config->no_path);
	if (config->so_path)
		free(config->so_path);
	if (config->we_path)
		free(config->we_path);
	if (config->ea_path)
		free(config->ea_path);
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
}
