/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:26 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/11 20:08:32 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_rotation_angle(char c)
{
	if (c == 'E')
		return (0);
	else if (c == 'N')
		return (PI / 2);
	else if (c == 'W')
		return (PI);
	else
		return ((PI * 3) / 2);
}

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
				vars->player.rotation_angle = get_rotation_angle(vars->map[vars->player.y][vars->player.x]);
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

void	line(t_vars *vars, int x_a, int y_a, int x_b, int y_b)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x_b - x_a);
	dy = abs(y_b - y_a);
	sx = (x_a < x_b) ? 1 : -1;
	sy = (y_a < y_b) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		mlx_pixel_put(vars->mlx, vars->win, x_a, y_a, 0xFFFFFF);
		if (x_a == x_b && y_a == y_b)
			break ;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x_a += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y_a += sy;
		}
	}
}

void	circle(t_vars *vars, int cx, int cy)
{
	int	radius;
	int	x;
	int	y;

	radius = 6;
	y = -1 * radius;
	while (y <= radius)
	{
		x = -1 * radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_pixel_put(vars->mlx, vars->win, cx + x, cy + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}
