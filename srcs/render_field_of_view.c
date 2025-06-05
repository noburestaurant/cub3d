/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_field_of_view.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:07:11 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 14:01:23 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_projected_wall_height(t_vars *vars)
{
	float	distance_to_wall;
	float	correct_distance_to_wall;
	float	distance_from_player_to_projected_plane;
	float	actual_wall_height;
	float	projected_wall_height;

	distance_to_wall = raycast(vars, vars->ray.ray_angle,
			vars->player.xplayer, vars->player.yplayer);
	if (distance_to_wall == 0.0)
		return (0);
	correct_distance_to_wall = distance_to_wall
		* cos(vars->ray.ray_angle - vars->player.rotation_angle);
	distance_from_player_to_projected_plane = (float)(WINDOW_WIDTH / 2)
		/ (tan(((float)FOV / (float)180 * PI) / (float)2));
	actual_wall_height = TILE_SIZE;
	projected_wall_height = actual_wall_height / correct_distance_to_wall
		* distance_from_player_to_projected_plane;
	return (projected_wall_height);
}

static void	render_wall_strip(t_vars *vars, float projected_wall_height, int i)
{
	int	j;

	init_render_info(vars, projected_wall_height);
	j = 0;
	get_rendering_wall_direction(vars);
	choose_rendering_wall_texture(vars);
	while (j < projected_wall_height)
	{
		get_pixel_color_and_render_it(vars, projected_wall_height, i, j);
		j++;
	}
	printf("\n");
}

void	render_field_of_view(t_vars *vars)
{
	int		i;
	float	projected_wall_height;

	i = 0;
	vars->player.xplayer = vars->player.x * 50 + (TILE_SIZE / 2);
	vars->player.yplayer = vars->player.y * 50 + (TILE_SIZE / 2);
	vars->ray.ray_angle = vars->player.rotation_angle
		- (((float)FOV / (float)180 * PI) / 2);
	vars->ray.delta_angle = (((float)FOV / (float)180) * PI) / WINDOW_WIDTH;
	while (i < WINDOW_WIDTH)
	{
		projected_wall_height = calc_projected_wall_height(vars);
		if (projected_wall_height == 0)
		{
			vars->ray.ray_angle += vars->ray.delta_angle;
			i++;
			continue ;
		}
		render_wall_strip(vars, projected_wall_height, i);
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
// support norm // ok
// add member of each structure // ok
// delete unnecessary variable and member of strcuture // ok
// int -> float as much as possible
// use floor() and ceil() to convert float to int
// 
// search
// support parse file
// map Error handling
// 
// name of functions and variables sould be easy to understand
// formula should be intuitive
// delete unnecessary part
// 	render_ray
// 	renga.xpm
// 	grass.xpm
// mlx Error handling
// memory leak
// fd leak
// support norm
// 
// support minimap (if you have nothing to do)

// issue
// 多分壁をレンダリングする位置を間違えてる // resolve
// 北のテクスチャに接近すると、南になる *sample.ber*
// セグフォを恐れてない
// 	*simple.ber* で南を向くとセグフォする
// レンダーするテクスチャの順番が左右逆
// 壁と壁の間をチラ見しがち (南東と北東) *peeking.ber*
// xpm file の height と width を指定するか、しないか
// 	vars->render_info.texture_height = TILE_SIZE ?

// memo
// 	line_length = 200 (probry 50 * sizeof(int))
// 	bits_per_pixel = 32
