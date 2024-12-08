/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:26 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/08 16:07:49 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_pos_p(t_vars *vars)
{
	vars->player.y = 0;
	while (vars->map[vars->player.y])
	{
		vars->player.x = 0;
		while (*((vars->map[vars->player.y]) + vars->player.x))
		{
			if (check_player(vars->map[vars->player.y][vars->player.x]))
			{
				vars->player.ort = vars->map[vars->player.y][vars->player.x];
				return ;
			}
			(vars->player.x)++;
		}
		(vars->player.y)++;
	}
}

void	measure(t_vars *vars)
{
	vars->width = 0;
	vars->height = 0;
	while (vars->map[vars->height])
		(vars->height)++;
	while (vars->map[0][vars->width])
		(vars->width)++;
}

char	**duplicate_map(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) * (vars->height + 1));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < vars->height)
	{
		map[i] = (char *)malloc(sizeof(char ) * (vars->width + 1));
		if (map[i] == NULL)
			return (NULL);
		j = 0;
		while (j < vars->width)
		{
			map[i][j] = vars->map[i][j];
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}

char	*ft_join_and_free(char *s1, char *s2)
{
	char	*ans;
	int		i;
	int		j;

	if (s1 == NULL)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		ans[i++] = s2[j++];
	ans[i] = '\0';
	free(s1);
	free(s2);
	return (ans);
}
