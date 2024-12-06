/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:26 by hnakayam          #+#    #+#             */
/*   Updated: 2024/08/31 16:14:15 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	get_pos_p(t_vars *vars)
{
	vars->y_p = 0;
	while (vars->map[vars->y_p])
	{
		vars->x_p = 0;
		while (*((vars->map[vars->y_p]) + vars->x_p))
		{
			if (vars->map[vars->y_p][vars->x_p] == 'P')
				return ;
			(vars->x_p)++;
		}
		(vars->y_p)++;
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
