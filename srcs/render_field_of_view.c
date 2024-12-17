/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_field_of_view.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:07:11 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/17 00:46:55by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_ray_facing_up(float ray_angle)
{
	return (sin(ray_angle) > 0);
}

int	is_ray_facing_down(float ray_angle)
{
	return (sin(ray_angle) < 0);
}

int	is_ray_facing_right(float ray_angle)
{
	return (cos(ray_angle) > 0);
}

int	is_ray_facing_left(float ray_angle)
{
	return (cos(ray_angle) < 0);
}

int	has_wall_at(t_vars *vars, int next_horizontal_touch_x,
	int next_horizontal_touch_y)
{
	int	coordinate_x_in_map;
	int	coordinate_y_in_map;

	coordinate_x_in_map = next_horizontal_touch_x / TILE_SIZE;
	coordinate_y_in_map = next_horizontal_touch_y / TILE_SIZE;
	return (vars->map[coordinate_y_in_map][coordinate_x_in_map] == '1');
}

double	calculate_distance_between_two_points(int a_x, int a_y,
	int b_x, int b_y)
{
	int	delta_x;
	int	delta_y;

	delta_x = b_x - a_x;
	delta_y = b_y - a_y;
	return (sqrt((delta_x) * (delta_x) + (delta_y) * (delta_y)));
}

float	calculate_wall_hit_distance_horizontal(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	int		next_horizontal_touch_x;
	int		next_horizontal_touch_y;
	// int		found_horz_wall;
	// int		wall_hit_x;
	// int		wall_hit_y;

	// calculate yintercept
	yintercept = (yplayer / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		yintercept += TILE_SIZE;
	// calculate xintercept
	xintercept = xplayer + ((yplayer - yintercept) / tan(ray_angle));
	// calculate ystep
	ystep = TILE_SIZE;
	if (is_ray_facing_up(ray_angle))
		ystep *= -1;
	// calculate xstep
	xstep = ystep / tan(ray_angle);
	if (is_ray_facing_left(ray_angle) && xstep > 0)
		xstep *= -1;
	if (is_ray_facing_right(ray_angle) && xstep < 0)
		xstep *= -1;
	// increment xstep and ystep until we find a wall
	next_horizontal_touch_x = xintercept;
	next_horizontal_touch_y = yintercept;
	vars->ray.horz_wall_hit_x = 0; // calloced so seems unnecessary // 前回１になってる可能性があるため必要
	vars->ray.horz_wall_hit_y = 0; // calloced so seems unnecessary // 前回１になってる可能性があるため必要
	vars->ray.found_horz_wall = 0; // calloced so seems unnecessary // 前回１になってる可能性があるため必要
	while (0 <= next_horizontal_touch_x && next_horizontal_touch_x <= WINDOW_WIDTH
		&& 0 <= next_horizontal_touch_y && next_horizontal_touch_y <= WINDOW_HEIGHT)
	{
		if (has_wall_at(vars, next_horizontal_touch_x, next_horizontal_touch_y - (is_ray_facing_up(ray_angle))))
		{
			vars->ray.found_horz_wall = 1;
			vars->ray.horz_wall_hit_x = next_horizontal_touch_x;
			vars->ray.horz_wall_hit_y = next_horizontal_touch_y;
			break ;
		}
		else
		{
			// increment xstep and ystep
			next_horizontal_touch_x += xstep;
			next_horizontal_touch_y += ystep;
		}
	}
	if (vars->ray.found_horz_wall != 1)
		return (0);
	return (calculate_distance_between_two_points(xplayer, yplayer,
		vars->ray.horz_wall_hit_x, vars->ray.horz_wall_hit_y));
}

float	calculate_wall_hit_distance_vertical(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	int		next_vertical_touch_x;
	int		next_vertical_touch_y;
	// int		found_vert_wall;
	// int		wall_hit_x;
	// int		wall_hit_y;

	// calculate xintercept
	xintercept = xplayer / TILE_SIZE * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		xintercept += TILE_SIZE;
	// calculate yintercept
	yintercept = yplayer - ((xintercept - xplayer) * tan(ray_angle));
	// calculate xstep
	xstep = TILE_SIZE;
	if (is_ray_facing_left(ray_angle) && xstep > 0)
		xstep *= -1;
	// calculate ystep
	ystep = xstep * tan(ray_angle);
	if (is_ray_facing_up(ray_angle) && ystep > 0)
		ystep *= -1;
	if (is_ray_facing_down(ray_angle) && ystep < 0)
		ystep *= -1;
	// increment xstep and ystep until we find a wall
	next_vertical_touch_x = xintercept;
	next_vertical_touch_y = yintercept;
	vars->ray.vert_wall_hit_x = 0; // calloced so seems unnecessary // 前回１になってる可能性があるため必要
	vars->ray.vert_wall_hit_y = 0; // calloced so seems unnecessary // 前回１になってる可能性があるため必要
	vars->ray.found_vert_wall = 0; // calloced so seems unnecessary // 前回１になってる可能性があるため必要
	while (0 <= next_vertical_touch_x && next_vertical_touch_x < WINDOW_WIDTH
		&& 0 <= next_vertical_touch_y && next_vertical_touch_y < WINDOW_HEIGHT)
	{
		if (has_wall_at(vars, next_vertical_touch_x - (is_ray_facing_left(ray_angle)), next_vertical_touch_y))
		{
			vars->ray.found_vert_wall = 1;
			vars->ray.vert_wall_hit_x = next_vertical_touch_x;
			vars->ray.vert_wall_hit_y = next_vertical_touch_y;
			break ;
		}
		else
		{
			// increment xstep and ystep
			next_vertical_touch_x += xstep;
			next_vertical_touch_y += ystep;
		}
	}
	if (vars->ray.found_vert_wall != 1)
		return (0);
	return (calculate_distance_between_two_points(xplayer, yplayer,
		vars->ray.vert_wall_hit_x, vars->ray.vert_wall_hit_y));
}

int	raycast(t_vars *vars, float ray_angle, int xplayer, int yplayer)
{
	float	len;
	float	distance_horz;
	float	distance_vert;

	len = 0;
	distance_horz = calculate_wall_hit_distance_horizontal
		(vars, ray_angle, xplayer, yplayer);
	distance_vert = calculate_wall_hit_distance_vertical
		(vars, ray_angle, xplayer, yplayer);
	if (distance_horz == 0 || distance_vert == 0)
	{
		if (distance_horz == 0)
		{
			vars->ray.wall_hit_x = vars->ray.vert_wall_hit_x;
			vars->ray.wall_hit_y = vars->ray.vert_wall_hit_y;
			return (distance_vert);
		}
		else if (distance_vert == 0)
		{
			vars->ray.wall_hit_x = vars->ray.horz_wall_hit_x;
			vars->ray.wall_hit_y = vars->ray.horz_wall_hit_y;
			return (distance_horz);
		}
	}
	if (distance_horz > distance_vert)
	{
		vars->ray.wall_hit_x = vars->ray.vert_wall_hit_x;
		vars->ray.wall_hit_y = vars->ray.vert_wall_hit_y;
		len = distance_vert;
	}
	else
	{
		vars->ray.wall_hit_x = vars->ray.horz_wall_hit_x;
		vars->ray.wall_hit_y = vars->ray.horz_wall_hit_y;
		len = distance_horz;
	}
	return (len);
}

	// if (vars->ray.found_vert_wall == 1 && distance_horz > distance_vert)
	// {
	// 	vars->ray.wall_hit_x = vars->ray.vert_wall_hit_x;
	// 	vars->ray.wall_hit_y = vars->ray.vert_wall_hit_y;
	// 	len = distance_vert;
	// }
	// else if (vars->ray.found_horz_wall == 1 && distance_horz <= distance_vert)
	// {
	// 	vars->ray.wall_hit_x = vars->ray.horz_wall_hit_x;
	// 	vars->ray.wall_hit_y = vars->ray.horz_wall_hit_y;
	// 	len = distance_horz;
	// }

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
// 	resolve a problem "wall_hit_x, wall_hit_y"
//	calculate direction of printed texture
//	get data of texture of each direction
//	get to know how to use the mlx_get_data_addr function
//	calculate the direction of printing wall // next

// issue
// 多分壁をレンダリングする位置を間違えてる

void	render_field_of_view(t_vars *vars)
{
	int		i;
	int		xplayer;
	int		yplayer;
	// float	ray_angle;
	// float	delta_angle; // can i remove it?

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
		// render a wall where col is i
		// line(vars,
		// 	WINDOW_WIDTH - i,
		// 	(WINDOW_HEIGHT / 2) - (projected_wall_height / 2),
		// 	WINDOW_WIDTH - i,
		// 	(WINDOW_HEIGHT / 2) + (projected_wall_height / 2));

		// select which cell will be printed
		int	texture_x = 0;
		int	texture_y = 0;
		int	texture_height = TILE_SIZE; // ホントはget_imgしたときの変数を使う
		// int	texture_width = TILE_SIZE;
		int	color_offset;
		int	color;
		int	j = 0;

		// int	print_north_texture; // ? 1 : 0
		// int	print_south_texture; // ? 1 : 0
		// int	print_east_texture; // ? 1 : 0
		// int	print_west_texture; // ? 1 : 0

		// if (print_north_texture)
		// 	texture_x = vars->ray.wall_hit_x % TILE_SIZE;
		// if (print_south_texture)
		// 	texture_x = TILE_SIZE - (vars->ray.wall_hit_x % TILE_SIZE);
		// if (print_east_texture)
		// 	texture_x = vars->ray.wall_hit_y % TILE_SIZE;
		// if (print_west_texture)
		// 	texture_x = TILE_SIZE - (vars->ray.wall_hit_y % TILE_SIZE);

		// calculate printing wall direction
		int	wall_direction = 0;
		// if (vars->ray.wall_hit_y % TILE_SIZE == 0)
		// {
		// 	if (vars->player.x < (int)vars->ray.wall_hit_x)
		// 		wall_direction = 2;
		// 	else
		// 		wall_direction = 3;
		// }
		// if (vars->ray.wall_hit_x % TILE_SIZE == 0)
		// {
		// 	if (vars->player.y > (int)vars->ray.wall_hit_y)
		// 		wall_direction = 0;
		// 	else
		// 		wall_direction = 1;
		// }
		if (vars->ray.wall_hit_y % TILE_SIZE == 0)
		{
			printf("vars->player.y = %d, (int)vars->ray.wall_hit_y = %d\n",
				vars->player.y * TILE_SIZE, (int)vars->ray.wall_hit_y);
			if (vars->player.y * TILE_SIZE > (int)vars->ray.wall_hit_y) // north // player.y is mapindex so it should be (player.y * TILE_SIZE)
			{
				printf("is north\n");
				wall_direction = 0;
			}
			else // south
			{
				printf("is south\n");
				wall_direction = 1;
			}
		}
		if (vars->ray.wall_hit_x % TILE_SIZE == 0)
		{
			// printf("vars->ray.wall_hit_x = %d\n", vars->ray.wall_hit_x);
			if (vars->player.x * TILE_SIZE < (int)vars->ray.wall_hit_x) // east
			{
				printf("is east\n");
				wall_direction = 2;
			}
			else // west
			{
				printf("is west\n");
				wall_direction = 3;
			}
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
			// printf("%d %% %d = %d\n", vars->ray.wall_hit_y, TILE_SIZE, texture_x);
			draw_wall = &(vars->textures->texture_east);
		}
		else if (wall_direction == 3) // west
		{
			texture_x = TILE_SIZE - (vars->ray.wall_hit_y % TILE_SIZE);
			draw_wall = &(vars->textures->texture_west);
		}
		else
		{
			write(2, "Error\n", 6);
			exit(1);
		}

		printf("texture_x = %d\n", texture_x);
		printf("wall_direction = %d\n", wall_direction);
		// printf(" = %d\n", );

		int	wall_start_y = (WINDOW_HEIGHT / 2) - (projected_wall_height / 2);

		while (j < projected_wall_height)
		{
			texture_y = j * texture_height / projected_wall_height;
			// color_offset = texture_y * vars->textures->texture_east.line_length
			// 	+ (texture_x * (vars->textures->texture_east.bits_per_pixel / 8));
			color_offset = texture_y * draw_wall->line_length
				+ (draw_wall->line_length - (texture_x * (draw_wall->bits_per_pixel / 8)));
			// color = *(int *)(addr + color_offset);
			color = *(int *)(draw_wall->addr + color_offset); // sample
			// mlx_pixel_put(vars->mlx, // maybe wrong
			// 	vars->win,
			// 	i,
			// 	WINDOW_HEIGHT / 2 - j,
			// 	color);
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

// memo
// 	line_length = 200 (probry 50 * sizeof(int))
// 	bits_per_pixel = 32
