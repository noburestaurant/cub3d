/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:44:12 by hnakayam          #+#    #+#             */
/*   Updated: 2025/05/24 23:55:24 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_args(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (!ft_strnstr(&file[len - 4], ".cub", 4))
		error_message_and_free(NULL, "Invalid file name", 1);
}

void	check_rectangular(t_vars *vars)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = -1;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			j++;
		}
		if (len == -1)
			len = j;
		else
		{
			if (j != len) // これはなくなると思う 長方形じゃないかもしれない
				error_message_and_free(vars, "Invalid map\n", 1);
		}
		i++;
	}
}

void	surrounded_by_wall(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->width)
	{
		if (vars->map[0][i] != '1')
			error_message_and_free(vars, "Invalid map\n", 1);
		if (vars->map[vars->height - 1][i] != '1')
			error_message_and_free(vars, "Invalid map\n", 1);
		i++;
	}
	i = 0;
	while (i < vars->height)
	{
		if (vars->map[i][0] != '1')
			error_message_and_free(vars, "Invalid map\n", 1);
		if (vars->map[i][vars->width - 1] != '1')
			error_message_and_free(vars, "Invalid map\n", 1);
		i++;
	}
}

void	check_components(t_vars *vars)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (check_player(vars->map[i][j]))
				player_count++;
			else if (vars->map[i][j] != '0' && vars->map[i][j] != '1')
				error_message_and_free(vars, "Invalid map\n", 1);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		error_message_and_free(vars, "Invalid map\n", 1);
}

void	parse_map(t_vars *vars)
{
	check_rectangular(vars);
	measure(vars);
	surrounded_by_wall(vars);
	check_components(vars);
	get_pos_p(vars);
	check_valid_path(vars);
}
