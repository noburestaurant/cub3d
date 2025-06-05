/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_texture_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 14:01:23 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_north_south_texture(t_vars *vars)
{
	if (vars->render_info.wall_direction == 1)
	{
		vars->render_info.texture_x = vars->ray.wall_hit_x % TILE_SIZE;
		vars->render_info.rendering_wall = &(vars->textures->texture_north);
	}
	else if (vars->render_info.wall_direction == 2)
	{
		vars->render_info.texture_x = TILE_SIZE
			- (vars->ray.wall_hit_x % TILE_SIZE);
		vars->render_info.rendering_wall = &(vars->textures->texture_south);
	}
}

static void	set_east_west_texture(t_vars *vars)
{
	if (vars->render_info.wall_direction == 3)
	{
		vars->render_info.texture_x = vars->ray.wall_hit_y % TILE_SIZE;
		vars->render_info.rendering_wall = &(vars->textures->texture_east);
	}
	else if (vars->render_info.wall_direction == 4)
	{
		vars->render_info.texture_x = TILE_SIZE
			- (vars->ray.wall_hit_y % TILE_SIZE);
		vars->render_info.rendering_wall = &(vars->textures->texture_west);
	}
}

void	choose_rendering_wall_texture(t_vars *vars)
{
	if (vars->render_info.wall_direction == 1
		|| vars->render_info.wall_direction == 2)
		set_north_south_texture(vars);
	else if (vars->render_info.wall_direction == 3
		|| vars->render_info.wall_direction == 4)
		set_east_west_texture(vars);
	else if (vars->render_info.wall_direction == 0)
	{
		write(2, "Unexpected Error\n", 17);
		exit(11);
	}
}

void	get_pixel_color_and_render_it(t_vars *vars, float projected_wall_height,
	int i, int j)
{
	vars->render_info.texture_y = j
		* (vars->render_info.texture_height / projected_wall_height);
	vars->render_info.color_offset = vars->render_info.texture_y
		* vars->render_info.rendering_wall->line_length
		+ (vars->render_info.texture_x
			* (vars->render_info.rendering_wall->bits_per_pixel / 8));
	vars->render_info.color = *(int *)(vars->render_info.rendering_wall->addr
			+ vars->render_info.color_offset);
	mlx_pixel_put(vars->mlx,
		vars->win,
		WINDOW_WIDTH - i - 1,
		vars->render_info.start_y + j,
		vars->render_info.color);
}

void	get_rendering_wall_direction(t_vars *vars)
{
	if (vars->render_info.horizontal_plane == 1)
	{
		if (vars->player.y * TILE_SIZE + (TILE_SIZE / 2)
			> (int)vars->ray.wall_hit_y)
			vars->render_info.wall_direction = 1;
		else
			vars->render_info.wall_direction = 2;
	}
	if (vars->render_info.horizontal_plane == 0)
	{
		if (vars->player.x * TILE_SIZE + (TILE_SIZE / 2)
			< (int)vars->ray.wall_hit_x)
			vars->render_info.wall_direction = 3;
		else
			vars->render_info.wall_direction = 4;
	}
}
