/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:01:16 by hnakayam          #+#    #+#             */
/*   Updated: 2024/08/29 20:21:43 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	error_message_and_free(t_vars *vars, char *msg, int status)
{
	if (vars != NULL)
	{
		free_img(vars);
		free_map(vars->map);
		if (vars->mlx != NULL && vars->win != NULL)
			mlx_destroy_window(vars->mlx, vars->win);
		if (vars->mlx != NULL)
			mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	ft_printf("%s", msg);
	exit(status);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_img(t_vars *vars)
{
	if (vars != NULL)
	{
		if (vars->img_renga != NULL)
			mlx_destroy_image(vars->mlx, vars->img_renga);
		if (vars->img_grass != NULL)
			mlx_destroy_image(vars->mlx, vars->img_grass);
		if (vars->img_goal != NULL)
			mlx_destroy_image(vars->mlx, vars->img_goal);
		if (vars->img_coin != NULL)
			mlx_destroy_image(vars->mlx, vars->img_coin);
		if (vars->img_player != NULL)
			mlx_destroy_image(vars->mlx, vars->img_player);
	}
}
