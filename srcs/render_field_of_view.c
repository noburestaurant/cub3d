/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_field_of_view.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:07:11 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/19 22:21:48 by hnakayam         ###   ########.fr       */
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
	printf("wall_hit_x = %d\n", vars->ray.wall_hit_x);
	printf("wall_hit_y = %d\n", vars->ray.wall_hit_y);
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

void	choose_rendering_wall_texture(t_vars *vars)
{
	if (vars->render_info.wall_direction == 1)
	{
		// printf("north wall\n");
		vars->render_info.texture_x = vars->ray.wall_hit_x % TILE_SIZE;
		vars->render_info.rendering_wall = &(vars->textures->texture_north);
	}
	else if (vars->render_info.wall_direction == 2)
	{
		// printf("south wall\n");
		vars->render_info.texture_x = TILE_SIZE
			- (vars->ray.wall_hit_x % TILE_SIZE);
		vars->render_info.rendering_wall = &(vars->textures->texture_south);
	}
	else if (vars->render_info.wall_direction == 3)
	{
		// printf("east wall\n");
		vars->render_info.texture_x = vars->ray.wall_hit_y % TILE_SIZE;
		vars->render_info.rendering_wall = &(vars->textures->texture_east);
	}
	else if (vars->render_info.wall_direction == 4)
	{
		// printf("west wall\n");
		vars->render_info.texture_x = TILE_SIZE
			- (vars->ray.wall_hit_y % TILE_SIZE);
		vars->render_info.rendering_wall = &(vars->textures->texture_west);
	}
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

void	render_field_of_view(t_vars *vars)
{
	int		i;
	int		j;
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
		printf("projected_wall_height = %.2f\n", projected_wall_height);
		// printf("wall_hit_y = %d, wall_hit_x == %d\n",
		// 	vars->ray.wall_hit_y, vars->ray.wall_hit_x);
		if (projected_wall_height == 0)
		{
			vars->ray.ray_angle += vars->ray.delta_angle;
			i++;
			continue ;
		}
		init_render_info(vars, projected_wall_height);
		j = 0;
		get_rendering_wall_direction(vars);
		printf("vars->render_info.wall_direction = %d\n", vars->render_info.wall_direction);
		choose_rendering_wall_texture(vars);
		while (j < projected_wall_height)
		{
			get_pixel_color_and_render_it(vars, projected_wall_height, i, j);
			j++;
		}
		printf("\n");
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
