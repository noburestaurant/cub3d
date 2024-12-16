/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:07:11 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/16 23:31:22 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_walk_direction(t_vars *vars)
{
	int		line_of_len;
	int		x_window;
	int		y_window;
	float	angle;

	x_window = vars->player.x * 50 + (TILE_SIZE / 2);
	y_window = vars->player.y * 50 + (TILE_SIZE / 2);
	angle = normalize_angle(vars->player.rotation_angle);
	line_of_len = 100;
	line(vars,
		x_window,
		y_window,
		x_window + (line_of_len * cos(angle)),
		y_window - (line_of_len * sin(angle)));
}

void	choose_image(t_vars *vars, int x, int y)
{
	if (vars->map[y][x] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img_renga, x * 50, y * 50);
	else
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->img_grass, x * 50, y * 50);
	// else if (vars->map[y][x] == '0')
	// 	mlx_put_image_to_window(vars->mlx, vars->win,
	// 		vars->img_grass, x * 50, y * 50);
	// else if (check_player(vars->map[y][x]))
	// {
	// 	mlx_put_image_to_window(vars->mlx, vars->win,
	// 		vars->img_grass, x * 50, y * 50);
	// 	circle(vars, (x * 50 + (TILE_SIZE / 2)), (y * 50 + (TILE_SIZE / 2)));
	// 	orientation(vars);
	// 	// put_walk_direction(vars); // test
	// }
}

int	is_ray_facing_up(float ray_angle)
{
	// printf("sin(%.2fPI) = %.2f\n", ray_angle / PI, sin(ray_angle));
	return (sin(ray_angle) > 0);
	// return (0 < ray_angle && ray_angle < PI);
}

int	is_ray_facing_down(float ray_angle)
{
	return (sin(ray_angle) < 0);
	// return (!is_ray_facing_up(ray_angle) && !is_equal(ray_angle, PI));
}

int	is_ray_facing_right(float ray_angle)
{
	// printf("cos(%.2fPI = %.2f\n", ray_angle / PI, cos(ray_angle));
	return (cos(ray_angle) > 0);
	// return ((0 < ray_angle && ray_angle < PI / 2) || (PI * 3 / 2 < ray_angle));
}

int	is_ray_facing_left(float ray_angle)
{
	return (cos(ray_angle) < 0);
	// return (!is_ray_facing_right(ray_angle) && !is_equal(ray_angle, PI / 2)
	// 	&& (is_equal(ray_angle, PI * 3 / 2)));
}

// if (has_wall_at(next_horizontal_touch_x, next_horizontal_touch_y)) // have to create
int	has_wall_at(t_vars *vars, int next_horizontal_touch_x, int next_horizontal_touch_y)
{
	int	coordinate_x_in_map;
	int	coordinate_y_in_map;

	coordinate_x_in_map = next_horizontal_touch_x / TILE_SIZE;
	coordinate_y_in_map = next_horizontal_touch_y / TILE_SIZE;
	return (vars->map[coordinate_y_in_map][coordinate_x_in_map] == '1');
}

double	calculate_distance_between_two_points(int a_x, int a_y, int b_x, int b_y)
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
	int		found_horz_wall;
	int		wall_hit_x;
	int		wall_hit_y;

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
	wall_hit_x = 0;
	wall_hit_y = 0;
	found_horz_wall = 0;
	while (0 <= next_horizontal_touch_x && next_horizontal_touch_x <= WINDOW_WIDTH
		&& 0 <= next_horizontal_touch_y && next_horizontal_touch_y <= WINDOW_HEIGHT)
	{
		if (has_wall_at(vars, next_horizontal_touch_x, next_horizontal_touch_y - (is_ray_facing_up(ray_angle))))
		{
			found_horz_wall = 1;
			wall_hit_x = next_horizontal_touch_x;
			wall_hit_y = next_horizontal_touch_y - (is_ray_facing_up(ray_angle));
			break ;
		}
		else
		{
			// increment xstep and ystep
			next_horizontal_touch_x += xstep;
			next_horizontal_touch_y += ystep;
		}
	}
	if (wall_hit_x == 0 && wall_hit_y == 0)
		return (0);
	// calculate the distance froom point(xplayer, yplayer) to
	// 	point(wall_hit_x, wall_hit_y) and return it
	return (calculate_distance_between_two_points(xplayer, yplayer, wall_hit_x, wall_hit_y));
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
	int		found_vert_wall;
	int		wall_hit_x;
	int		wall_hit_y;

	// calculate xintercept
	xintercept = xplayer / TILE_SIZE * TILE_SIZE; // floor(xplayer / TILE_SIZE) ?
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
	wall_hit_x = 0;
	wall_hit_y = 0;
	found_vert_wall = 0;
	while (0 <= next_vertical_touch_x && next_vertical_touch_x < WINDOW_WIDTH
		&& 0 <= next_vertical_touch_y && next_vertical_touch_y < WINDOW_HEIGHT)
	{
		if (has_wall_at(vars, next_vertical_touch_x - (is_ray_facing_left(ray_angle)), next_vertical_touch_y))
		{
			found_vert_wall = 1;
			wall_hit_x = next_vertical_touch_x - (is_ray_facing_left(ray_angle));
			wall_hit_y = next_vertical_touch_y;
			break ;
		}
		else
		{
			// increment xstep and ystep
			next_vertical_touch_x += xstep;
			next_vertical_touch_y += ystep;
		}
	}
	if (wall_hit_x == 0 && wall_hit_y == 0)
		return (0);
	return (calculate_distance_between_two_points(xplayer, yplayer, wall_hit_x, wall_hit_y));
}

int	raycast(t_vars *vars, float ray_angle, int xplayer, int yplayer)
{
	float	len;
	float	distance_horz;
	float	distance_vert;

	distance_horz = calculate_wall_hit_distance_horizontal(vars, ray_angle, xplayer, yplayer);
	// distance_horz = 0;
	distance_vert = calculate_wall_hit_distance_vertical(vars, ray_angle, xplayer, yplayer);
	// distance_vert = 0;

	if (distance_horz == 0 || distance_vert == 0)
	{
		if (distance_horz == 0)
			return (distance_vert);
		else if (distance_vert == 0)
			return (distance_horz);
	}
	if (distance_horz > distance_vert)
		len = distance_vert;
	else
		len = distance_horz;
	return (len);
}

// get the point where the ray hits the wall in horizontal
// 	find coordinate of the first horizontal intersection
// 		xintercept = xplayer + ((yplayer - yintercept) / tan(ray_angle))
// 		yintercept = yplayer / TILE_SIZE * TILE_SIZE
// 	find xstep and ystep
// 		xstep = ystep / tan(ray_angle)
// 		ystep = TILE_SIZE
// 	convert intersection point into map index
// 		(x, y) -> map[i][j]
// 	check if intersection hits a wall
// 		yes -> store horizontal hit distance
// 		no  -> find next horizontal intersection
// get the point where the ray hits the wall in vertical
// 	find coordinate of the first vertical intersection
// 		xintercept = xplayer / TILE_SIZE * TILE_SIZE + 1
// 		yintercept = yplayer - ((xintercept - xplayer) * tan(ray_angle))
// 	find xstep and ystep
// 		xstep = TILE_SIZE
// 		ystep = xstep * tan(ray_angle)
// 	convert intersection point into map index
// 	check if intersection hits a wall
// compare lengths of those rays and select the smallest one

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
//	calculate direction of printed texture
//	get data of texture of each direction
//	get to know how to use the mlx_get_data_addr function

void	render_field_of_view(t_vars *vars)
{
	int		i;
	int		x_window;
	int		y_window;
	float	ray_angle;
	float	d_angle;

	float	distance_to_wall;
	float	correct_distance_to_wall;
	float	distance_from_player_to_projected_plane;
	float	actual_wall_height;
	float	projected_wall_height;

	i = 0;
	x_window = vars->player.x * 50 + (TILE_SIZE / 2);
	y_window = vars->player.y * 50 + (TILE_SIZE / 2);
	ray_angle = vars->player.rotation_angle - (((float)FOV / (float)180 * PI) / 2);
	d_angle = (((float)FOV / (float)180) * PI) / WINDOW_WIDTH;
	while (i < WINDOW_WIDTH)
	{
		// calculate length of a wall which will be rendered
		distance_to_wall = raycast(vars, ray_angle, x_window, y_window);
		correct_distance_to_wall = distance_to_wall
			* cos(ray_angle - vars->player.rotation_angle);
		distance_from_player_to_projected_plane = (float)(WINDOW_WIDTH / 2)
			/ (tan(((float)FOV / (float)180 * PI) / (float)2));
		actual_wall_height = TILE_SIZE;
		projected_wall_height = actual_wall_height / correct_distance_to_wall
			* distance_from_player_to_projected_plane;
		// render a wall where col is i
		line(vars,
			WINDOW_WIDTH - i,
			(WINDOW_HEIGHT / 2) - (projected_wall_height / 2),
			WINDOW_WIDTH - i,
			(WINDOW_HEIGHT / 2) + (projected_wall_height / 2));

		// // select which cell will be printed
		// int	i = 0;
		// int	texture_x = 0;
		// int	texture_y = 0;
		// int	texture_height = TILE_SIZE;
		// int	texture_width = TILE_SIZE;
		// int	print_north_texture; // ? 1 : 0
		// int	print_south_texture; // ? 1 : 0
		// int	print_east_texture; // ? 1 : 0
		// int	print_west_texture; // ? 1 : 0
		// int	color_offset;
		// int	color;
		// if (print_north_texture)
		// 	texture_x = wall_hit_x % TILE_SIZE;
		// if (print_south_texture)
		// 	texture_x = TILE_SIZE - (wall_hit_x % TILE_SIZE);
		// if (print_east_texture)
		// 	texture_x = wall_hit_y % TILE_SIZE;
		// if (print_west_texture)
		// 	texture_x = TILE_SIZE - (wall_hit_y % TILE_SIZE);
		// while (j < projected_wall_height)
		// {
		// 	texture_y = i * texture_height / projected_wall_height;
		// 	color_offset = texture_y * line_lenght + texture_x;
		// 	color = *(int *)(addr + color_offset);
		// 	mlx_pixel_put(vars->mlx,
		// 		vars->win, i, WINDOW_HEIGHT / 2 - j, color);
		// 	i++;
		// }

		ray_angle += d_angle;
		i++;
	}
}

// void	print_player(t_vars *vars)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < vars->height)
// 	{
// 		x = 0;
// 		while (x < vars->width)
// 		{
// 			if (check_player(vars->map[y][x]))
// 			{
// 				circle(vars, (x * 50 + (TILE_SIZE / 2)),
// 					(y * 50 + (TILE_SIZE / 2)));
// 				print_orientation(vars);
// 				render_field_of_view(vars, x, y);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	render_map(t_vars *vars)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < vars->height)
// 	{
// 		x = 0;
// 		while (x < vars->width)
// 		{
// 			choose_image(vars, x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// 	print_player(vars);
// }

void	print_player(t_vars *vars)
{
	circle(vars, (vars->player.x * 50 + (TILE_SIZE / 2)),
		(vars->player.y * 50 + (TILE_SIZE / 2)));
	print_orientation(vars);
}

void	render_map(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			choose_image(vars, x, y);
			x++;
		}
		y++;
	}
}
