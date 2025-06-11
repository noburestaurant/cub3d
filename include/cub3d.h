/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:59:26 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:46:41 by hnakayam         ###   ########.fr       */
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

typedef struct s_parse_data
{
	int		height;
	int		max_width;
	int		in_map_section;;
	char	**raw_map;
	char	*error_msg;
}	t_parse_data;

typedef struct s_texture
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color[3];
	int		ceil_color[3];
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_floor;
	int		has_ceil;
}	t_config;

typedef struct s_texture_list
{
	t_texture	texture_north;
	t_texture	texture_south;
	t_texture	texture_east;
	t_texture	texture_west;
}	t_texture_list;

typedef struct s_img_player
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
}	t_img_player;

typedef struct s_player
{
	char	ort;
	float	rotation_angle;
	float	walk_direction;
	int		xplayer; // window coordinate
	int		yplayer; // window coordinate
	int		x; // map index
	int		y; // map index
}	t_player;

typedef struct s_ray
{
	float	ray_angle;
	float	delta_angle;
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	int		found_horz_wall;
	int		found_vert_wall;
	int		horz_wall_hit_x;
	int		horz_wall_hit_y;
	int		vert_wall_hit_x;
	int		vert_wall_hit_y;
	int		wall_hit_x;
	int		wall_hit_y;
}	t_ray;

typedef struct s_render_wall
{
	int			horizontal_plane;
	int			texture_x;
	int			texture_y;
	int			texture_height;
	int			wall_direction;
	int			color_offset;
	int			color;
	t_texture	*rendering_wall;
	int			start_y;
}	t_render_wall;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_img_player	*img_player;
	void			*img_renga;
	void			*img_grass;
	t_texture_list	*textures;
	t_config		config;  // 設定情報
	char			**map;
	t_player		player;
	t_ray			ray;
	t_render_wall	render_info;
	int				img_width;
	int				img_height;
	int				width; // necessary ?
	int				height; // necessary ?
}	t_vars;

/* parsing section*/
int		validate_color_count(char **parts, char **error_msg);
int		check_digit_only(char *str);
int		validate_color_value(char *part, int *color_val, char **error_msg);
void	free_color_parts(char **parts);
int		is_valid_color_format(char *color_str, int color[3], char **error_msg);
int		is_valid_texture_path(char *path, char **error_msg);
int		handle_duplicate_config(int has_config, char **error_msg, char *value);
int		process_texture_config(char *value, char **path, char **error_msg);
int		process_color_config(char *value, int *color, char **error_msg);
int		handle_no_config(t_config *config, char *value, char **error_msg);
int		handle_so_config(t_config *config, char *value, char **error_msg);
int		handle_we_config(t_config *config, char *value, char **error_msg);
int		handle_ea_config(t_config *config, char *value, char **error_msg);
int		handle_floor_config(t_config *config, char *value, char **error_msg);
int		handle_ceil_config(t_config *config, char *value, char **error_msg);
int		get_identifier_type(char *line);
char	*get_config_value(char *line, int type);
int		process_config_by_type(t_config *config, int type, char *value,
		char **error_msg);
int		parse_config_line(char *line, t_config *config, char **error_msg);
int		is_valid_map_line(char *line);
char	**alloc_two_dimensional_array(int height, int width);
char	**adjust_map_data(char **raw_map, int height, int width);
int		is_map_enclosed(char **map, int height, int width);
int		validate_player_position(char **map, int height, int width,
		int *player_count);
void	initialize_config(t_vars *vars);
int		validate_all_configs(t_vars *vars);
char	**allocate_raw_map(void);
void	process_first_map_line(t_vars *vars, char *line, t_parse_data *data);
void	start_map_section(char *line, t_parse_data *data, t_vars *vars);
void	handle_config_error(char *line, int fd, t_vars *vars, char *error_msg);
void	process_not_map_line(t_vars *vars, char *line, t_parse_data *data,
		int fd);
void	handle_map_line(char *line, t_parse_data *data);
void	process_map_line(t_vars *vars, char *line, t_parse_data *data);
void	handle_empty_line(char *line, int in_map_section, t_vars *vars);
void	parse_file_content(int fd, t_vars *vars, t_parse_data *data);
void	cleanup_raw_map(char **raw_map, int height);
void	validate_final_map(t_vars *vars, t_parse_data *data);
void	finalize_parsing(t_vars *vars, t_parse_data *data);
void	parse_cub_file(char *file_path, t_vars *vars);
void	validation_and_parse(int argc, char **argv, t_vars *vars);


int		check_player(char c);
int	is_valid_extension(char *filename);
char	*ft_join_and_free(char *s1, char *s2);
char	**get_map(char *file);
void	get_map_handle_error(char *crr_line, char *linked_lines);
void	init_vars(t_vars *vars);
void	check_args(char *file);
void	check_rectangular(t_vars *vars);
void	get_pos_p(t_vars *vars);
void	surrounded_by_wall(t_vars *vars);
void	measure(t_vars *vars);
void	check_components(t_vars *vars);
char	**duplicate_map(t_vars *vars);
void	parse_map(t_vars *vars);
void	choose_image(t_vars *vars, int x, int y);
void	render_map(t_vars *vars);
void	get_img(t_vars *vars);
void	convert_img_to_data_addr(t_vars *vars);
void	print_player(t_vars *vars);
void	render_field_of_view(t_vars *vars);
int		is_ray_facing_up(float ray_angle);
int		is_ray_facing_down(float ray_angle);
int		is_ray_facing_right(float ray_angle);
int		is_ray_facing_left(float ray_angle);
float	calculate_distance_between_two_points(int a_x, int a_y,
			int b_x, int b_y);
int		has_wall_at(t_vars *vars,
			int next_horizontal_touch_x, int next_horizontal_touch_y);
float	distance_vert_is_smallest(t_vars *vars, float distance_vert);
float	distance_horz_is_smallest(t_vars *vars, float distance_horz);
int		key_hook(int keycode, t_vars *vars);
void	reset_player(t_vars *vars, int x_before, int y_before);
void	update_map(t_vars *vars, int x_before, int y_before);
int		check_possible_to_move(t_vars *vars);
void	error_message_and_free(t_vars *t_vars, char *msg, int status);
void	free_map(char **map);
void	free_img(t_vars *vars);
int		window_close(t_vars *vars);
void	render_floor(t_vars *vars, int floor_color);
void	render_ceiling(t_vars *vars, int ceiling_color);
void	render_floor_and_ceiling(t_vars *vars);
float	raycast(t_vars *vars, float ray_angle, int xplayer, int yplayer);
void	init_render_info(t_vars *vars, float projected_wall_height);

// will be deleted
void	line(t_vars *vars, int x_a, int y_a, int x_b, int y_b);
void	circle(t_vars *vars, int cx, int cy);
float	normalize_angle(float angle);
int		is_equal(float a, float b);
void	print_orientation(t_vars *vars);
void	render_rays(t_vars *vars);
void	render_ray(t_vars *vars, float ray_angle, int xplayer, int yplayer);

#endif
