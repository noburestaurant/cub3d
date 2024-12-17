/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_field_of_view.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:07:11 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 03:15:10 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_field_of_view(t_vars *vars)
{
	int		i;
	int		xplayer;
	int		yplayer;

	float	distance_to_wall;
	float	correct_distance_to_wall;
	float	distance_from_player_to_projected_plane;
	float	actual_wall_height;
	float	projected_wall_height;

	i = 0;
	xplayer = vars->player.x * 50 + (TILE_SIZE / 2);
	yplayer = vars->player.y * 50 + (TILE_SIZE / 2);
	vars->ray.ray_angle = vars->player.rotation_angle
		- (((float)FOV / (float)180 * PI) / 2);
	vars->ray.delta_angle = (((float)FOV / (float)180) * PI) / WINDOW_WIDTH;
	while (i < WINDOW_WIDTH)
	{
		// calculate length of a wall which will be rendered
		distance_to_wall = raycast(vars, vars->ray.ray_angle, xplayer, yplayer);
		correct_distance_to_wall = distance_to_wall
			* cos(vars->ray.ray_angle - vars->player.rotation_angle);
		distance_from_player_to_projected_plane = (float)(WINDOW_WIDTH / 2)
			/ (tan(((float)FOV / (float)180 * PI) / (float)2));
		actual_wall_height = TILE_SIZE;
		projected_wall_height = actual_wall_height / correct_distance_to_wall
			* distance_from_player_to_projected_plane;

		// select which cell will be printed
		int	texture_x = 0;
		int	texture_y = 0;
		int	texture_height = TILE_SIZE; // ホントはget_imgしたときの変数を使う
		int	color_offset;
		int	color;
		int	j = 0;

		// calculate printing wall direction
		int	wall_direction = 0;
		if (vars->ray.wall_hit_y % TILE_SIZE == 0)
		{
			if (vars->player.y * TILE_SIZE > (int)vars->ray.wall_hit_y) // north
				wall_direction = 0;
			else // south
				wall_direction = 1;
		}
		if (vars->ray.wall_hit_x % TILE_SIZE == 0)
		{
			if (vars->player.x * TILE_SIZE < (int)vars->ray.wall_hit_x) // east
				wall_direction = 2;
			else // west
				wall_direction = 3;
		}

		// choose printing wall texture
		t_texture	*draw_wall;
		if (wall_direction == 0) // north
		{
			texture_x = vars->ray.wall_hit_x % TILE_SIZE;
			draw_wall = &(vars->textures->texture_north);
		}
		else if (wall_direction == 1) // south
		{
			texture_x = TILE_SIZE - (vars->ray.wall_hit_x % TILE_SIZE);
			draw_wall = &(vars->textures->texture_south);
		}
		else if (wall_direction == 2) // east
		{
			texture_x = vars->ray.wall_hit_y % TILE_SIZE;
			draw_wall = &(vars->textures->texture_east);
		}
		else if (wall_direction == 3) // west
		{
			texture_x = TILE_SIZE - (vars->ray.wall_hit_y % TILE_SIZE);
			draw_wall = &(vars->textures->texture_west);
		}

		// calclate printing color and render it
		int	wall_start_y = (WINDOW_HEIGHT / 2) - (projected_wall_height / 2);
		while (j < projected_wall_height)
		{
			texture_y = j * texture_height / projected_wall_height;
			color_offset = texture_y * draw_wall->line_length
				+ (draw_wall->line_length - (texture_x * (draw_wall->bits_per_pixel / 8)));
			color = *(int *)(draw_wall->addr + color_offset);
			mlx_pixel_put(vars->mlx,
				vars->win,
				i,
				wall_start_y + j,
				color);
			j++;
		}

		vars->ray.ray_angle += vars->ray.delta_angle;
		i++;
	}
}

// things to do
// create structure t_ray, t_texture
// 	typedef struct s_ray
// 	{
// 		int	hoge;
// 	}	t_ray;
// 	typedef struct s_texture
// 	{
// 		int	hoge;
// 	}	t_texture;
// resolve a problem "wall_hit_x, wall_hit_y"
// calculate direction of printed texture
// get data of texture of each direction
// get to know how to use the mlx_get_data_addr function
// calculate the direction of printing wall // ok
// delete unnecessary code and comment // ok
// render floor and ceiling // ok
// support norm
// add member of each structure
// delete unnecessary variable and member of strcuture
// mlx Error handling
// 
// search
// support parse file
// map Error handling
// 
// name of functions and variables sould be easy to understand
// formula should be intuitive
// memory leak
// fd leak
// support norm
// 
// support minimap (if you have nothing to do)

// issue
// 多分壁をレンダリングする位置を間違えてる // resolve
// 壁が近いと南北が逆になる
// 横の移動が正常の方向とは逆の方向になっている

// memo
// 	line_length = 200 (probry 50 * sizeof(int))
// 	bits_per_pixel = 32
