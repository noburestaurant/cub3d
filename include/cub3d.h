/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:59:26 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/16 22:46:02 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ESC 65307
# define W 119
# define S 115
# define A 97
# define D 100
# define RIGHT 65363
# define LEFT 65361

// nobu
# define PI 3.141592653589793
# define TILE_SIZE 50
# define MAP_NUM_ROWS 10
# define MAP_NUM_COLS 11
# define WINDOW_WIDTH 550 // MAP_NUM_COLS * TILE_SIZE
# define WINDOW_HEIGHT 500 // MAP_NUM_ROWS * TILE_SIZE
# define FOV 60
// # define MINIMAP_SCALE_FACTOR // when rendering any number, all value have to maltiply by the number

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include "ft_printf.h"

typedef struct s_player
{
	char	ort;
	float	rotation_angle;
	float	walk_direction;
	int		x;
	int		y;
}	t_player;

typedef struct s_ray
{
	int	wall_hit_x;
	int	wall_hit_y;
}	t_ray;

// typedef struct s_texture
// {
// 	int	*texture_north;
// 	int	*texture_south;
// 	int	*texture_east;
// 	int	*texture_west;
// }	t_texture;

typedef struct s_img_player
{
	void	*s;
	void	*n;
	void	*w;
	void	*e;
	void	*current;
}	t_img_player;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	void			*img_renga;
	void			*img_grass;
	void			*img_goal;
	void			*img_coin;
	t_img_player	*img_player;
	int				img_width;
	int				img_height;
	char			**map;
	int				width;
	int				height;
	t_player		player;
	int				move_count;
}	t_vars;

int		check_player(char c);

char	*ft_join_and_free(char *s1, char *s2);
char	**get_map(char *file);
void	get_map_handle_error(char *crr_line, char *linked_lines);
void	init_vars(t_vars *vars);
void	check_args(char *file);
void	check_rectangular(t_vars *vars);
void	get_pos_p(t_vars *vars);
int		flood_fill(t_vars *vars, char **map, int col, int row);
void	surrounded_by_wall(t_vars *vars);
void	measure(t_vars *vars);
void	check_components(t_vars *vars);
char	**duplicate_map(t_vars *vars);
void	check_no_c_in_map(char **duplicated_map, t_vars *vars);
void	check_valid_path(t_vars *vars);
void	parse_map(t_vars *vars);
void	get_img(t_vars *vars);
void	choose_image(t_vars *vars, int x, int y);
void	render_map(t_vars *vars);
void	print_player(t_vars *vars);
void	render_field_of_view(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);
void	reset_player(t_vars *vars, int x_before, int y_before);
void	update_map(t_vars *vars, int x_before, int y_before);
int		check_possible_to_move(t_vars *vars);
void	error_message_and_free(t_vars *t_vars, char *msg, int status);
void	free_map(char **map);
void	free_img(t_vars *vars);
int		window_close(t_vars *vars);

void	line(t_vars *vars, int x_a, int y_a, int x_b, int y_b);
void	circle(t_vars *vars, int cx, int cy);
float	normalize_angle(float angle);
int		is_equal(float a, float b);
void	print_orientation(t_vars *vars);

#endif
