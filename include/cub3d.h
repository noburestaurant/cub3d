/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:59:26 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/08 15:55:35 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ESC 65307
# define W 119
# define S 115
# define A 97
# define D 100
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include "ft_printf.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img_renga;
	void	*img_grass;
	void	*img_goal;
	void	*img_coin;
	void	*img_player;
	int		img_width;
	int		img_height;
	char	**map;
	int		width;
	int		height;
	int		x_p;
	int		y_p;
	int		c;
	int		p;
	int		e;
	int		move_count;
	int		enable;
	int		x;
	int		y;
}	t_vars;

typedef struct s_player
{
	char	ort;
	int		x;
	int		y;
}	t_player;

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
int		key_hook(int keycode, t_vars *vars);
void	reset_player(t_vars *vars, int x_before, int y_before);
void	update_map(t_vars *vars, int x_before, int y_before);
int		check_possible_to_move(t_vars *vars);
void	error_message_and_free(t_vars *t_vars, char *msg, int status);
void	free_map(char **map);
void	free_img(t_vars *vars);
int		window_close(t_vars *vars);

#endif
