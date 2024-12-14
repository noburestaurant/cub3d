/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:22:38 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/14 14:58:44 by hnakayam         ###   ########.fr       */
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

int	calculate_wall_hit_distance_horizontal(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	int	xstep;
	int	ystep;
	int	xintercept;
	int	yintercept;

	xintercept = xplayer + ((yplayer - yintercept) / tan(ray_angle));
	yintercept = yplayer / TILE_SIZE * TILE_SIZE; // floor(xplayer / TILE_SIZE) ?
	xstep = ystep / tan(ray_angle);
	ystep = TILE_SIZE;
	// if is_ray_facing_up
	// 	ystep *= -1;
	// if is_ray_facing_down
	// 	yintercept *= -1;
	// if is_ray_facing_left && xstep > 0
	// 	xstep *= -1;
	// if is_ray_facing_right && xstep < 0
	// 	xstep *= -1;

	// int	next_horizontal_touch_x = xintercept;
	// int	next_horizontal_touch_y = yintercept;
	// if is_ray_facing_up
	// 	next_horizontal_touch_y--; // touch y was right on the line
	// // increment xstep and ystep until we find a wall
	// int	found_horz_wall = 0;
	// int	wall_hit_x;
	// int	wall_hit_y;
	// while (...) // next_horizontal_touch is in the window
	// {
	// 	if has_wall_at(next_horizontal_touch_x, next_horizontal_touch_y) // have to create
	// 	{
	// 		found_horz_wall = 1;
	// 		wall_hit_x = next_horizontal_touch_x;
	// 		wall_hit_y = next_horizontal_touch_y;
	// 		// put line player to wall_hit to test
	// 		break ;
	// 	}
	// 	else
	// 	{
	// 		// increment xstep and ystep
	// 	}
	// }
}

int	calculate_wall_hit_distance_vertical(t_vars *vars, float ray_angle,
	int xplayer, int yplayer)
{
	int	xstep;
	int	ystep;
	int	xintercept;
	int	yintercept;

	xintercept = xplayer / TILE_SIZE * TILE_SIZE + 1; // floor(xplayer / TILE_SIZE) ?
	yintercept = yplayer - ((xintercept - xplayer) * tan(ray_angle));
	xstep = TILE_SIZE;
	ystep = xstep * tan(ray_angle);
}

int	raycast(t_vars *vars, float ray_angle, int xplayer, int yplayer)
{
	int	len;
	int	xstep;
	int	ystep;
	int	xintercept;
	int	yintercept;
	int	distance_horz;
	int	distance_vert;

	distance_horz = calculate_wall_hit_distance_horizontal(vars, ray_angle, xplayer, yplayer);
	distance_vert = calculate_wall_hit_distance_vertical(vars, ray_angle, xplayer, yplayer);
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

void	print_shaped_fan(t_vars *vars, int x, int y)
{
	int		i;
	int		len;
	int		x_window;
	int		y_window;
	int		x_to;
	int		y_to;
	float	ray_angle;
	float	d_angle;

	i = 0;
	len = 100;
	x_window = x * 50 + (TILE_SIZE / 2);
	y_window = y * 50 + (TILE_SIZE / 2);
	ray_angle = vars->player.rotation_angle - (((double)FOV / (double)180 * PI) / 2);
	d_angle = (((double)FOV / (double)180) * PI) / WINDOW_WIDTH;
	while (i < WINDOW_WIDTH)
	{
		// raycast(vars, ray_angle, x, y);
		/* render 3d projected walls function
		calculate projected wall height
		actual wall height / distance to the wall =
			rojected wall height / distance from player to the projected wall
			actual wall height = WINDOW_HEIGHT
			distance to the wall = return value of raycast()
				-> correct distance to the wall = return value of raycat() * cos(ray_angle - rotation_angle)
			projected wall height = 
			distance from player to the projected wall = (WINDOW_WIDTH / 2) / (tan(FOV(in radian) / 30))
		*/
		x_to = x_window + (len * cos(ray_angle));
		y_to = y_window - (len * sin(ray_angle));
		line(vars, x_window, y_window, x_to, y_to);
		ray_angle += d_angle;
		i++;
	}
}

void	print_player(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->height)
	{
		x = 0;
		while (x < vars->width)
		{
			if (check_player(vars->map[y][x]))
			{
				circle(vars, (x * 50 + (TILE_SIZE / 2)),
					(y * 50 + (TILE_SIZE / 2)));
				orientation(vars);
				print_shaped_fan(vars, x, y);
			}
			x++;
		}
		y++;
	}
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
	print_player(vars);
}
