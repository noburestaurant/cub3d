/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:00:37 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/17 17:56:49 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_handle_error(char *crr_line, char *linked_lines)
{
	if (crr_line != NULL && crr_line[0] == '\n')
	{
		free(linked_lines);
		free(crr_line);
		error_message_and_free(NULL, "Invalid map\n", 1);
	}
	if (linked_lines[0] == '\0')
	{
		free(linked_lines);
		free(crr_line);
		error_message_and_free(NULL, "Invalid args or map\n", 1);
	}
}

char	**get_map(char *file)
{
	int		fd;
	char	*crr_line;
	char	*linked_lines;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_message_and_free(NULL, "Invalid args\n", 1);
	linked_lines = ft_strdup("");
	while (1)
	{
		crr_line = get_next_line(fd);
		if (crr_line == NULL || crr_line[0] == '\n')
			break ;
		linked_lines = ft_join_and_free(linked_lines, crr_line);
		if (linked_lines == NULL)
			error_message_and_free(NULL, "Unxpected error\n", 1);
	}
	get_map_handle_error(crr_line, linked_lines);
	free(crr_line);
	map = ft_split(linked_lines, '\n');
	free(linked_lines);
	return (map);
}

void	get_img(t_vars *vars)
{
	vars->img_renga = mlx_xpm_file_to_image(vars->mlx, "./img/renga.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_renga == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_grass = mlx_xpm_file_to_image(vars->mlx, "./img/grass.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_grass == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->n = mlx_xpm_file_to_image(vars->mlx, "./img/player_n.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->n == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->s = mlx_xpm_file_to_image(vars->mlx, "./img/player_s.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->s == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->e = mlx_xpm_file_to_image(vars->mlx, "./img/player_e.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->e == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->w = mlx_xpm_file_to_image(vars->mlx, "./img/player_w.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->w == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);

	// get images of wall texture
	vars->img_player->north = mlx_xpm_file_to_image(vars->mlx, "./img/north",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->north == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->south = mlx_xpm_file_to_image(vars->mlx, "./img/south",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->south == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->east = mlx_xpm_file_to_image(vars->mlx, "./img/east",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->east == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->west = mlx_xpm_file_to_image(vars->mlx, "./img/west",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->west == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	
	// malloc texture variable
	vars->texture = (t_texture *)malloc(sizeof(t_texture) * 1);
	if (vars->texture == NULL)
		exit(1); // Error
	// convert img to addr
	vars->texture->texture_north = mlx_get_data
		(vars->img_player->north, , , );
	

	vars->img_player->current = vars->img_player->n;
}

void	init_vars(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->img_renga = NULL;
	vars->img_grass = NULL;
	vars->img_player = calloc(1, sizeof(t_vars) * 1);
	if (vars->img_player == NULL)
		exit (1); // error
	vars->img_player->n = NULL;
	vars->img_player->s = NULL;
	vars->img_player->e = NULL;
	vars->img_player->w = NULL;
	vars->map = NULL;
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		error_message_and_free(NULL, "Invalid args\n", 1);
	init_vars(&vars);
	check_args(argv[1]);
	vars.map = get_map(argv[1]);
	if (vars.map == NULL)
		error_message_and_free(&vars, "Unexpected Error\n", 1);
	parse_map(&vars);
	vars.move_count = 0;
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		error_message_and_free(&vars, "Unexpected Error: mlx\n", 1);
	vars.win = mlx_new_window(vars.mlx, vars.width * 50,
			vars.height * 50, "game");
	if (vars.win == NULL)
		error_message_and_free(&vars, "Unexpected Error: mlx\n", 1);
	get_img(&vars);
	// render_map(&vars);
	// print_player(&vars);
	// render_rays(&vars);
	// print_orientation(&vars);
	render_field_of_view(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, window_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

// '0' '1' 'C' 'E' 'P' 以外のものがないか
// '1' でかこわれているか
// 'E', 'P', 'C' は一つずつあるか

// flood_fillでマップが変わっていないか ok
// 画像を作る ok
// マップを出力する関数 ok
// キーイベント（shige参考）ok
// マップの更新 ok
// Cをすべて通ってゴールできるか ok

// support movecount ok
// printf should be ft_printf
// norm ok
// make file (cflag) ok
// ignoring return value of write
// レビュー項目を実施
// map directory? texture directory?

// ./cub3d ber でエラーにならな ok
// ./cub3d 1.bers でエラーにならない ok
// file が空だったときにSEGV ok
// file が改行だけのときにSEGV ok
// 2.ber のときは正常に機能(確認する)
// バツを押すとウィンドウが閉じられない ok
// doesnt support as the player can finish ok
// the game only after picking every collectible ok
// has to support arrow key ok
// free ok

// norminette
	// ft_splitのヘッダー // ok
// strchr -> strnstr // ok
	// check_args関数 (edge case example: "../cub3d/test.ber")
// leaks // ok
// valgrind --leak-check=full --show-leak-kinds=all ./your_program_file [args]
// 1 get_map func // ok
// 	char **map = ft_split();
// 	free(linked_lines);
// 2 mlx (click the cross button, push ESC key, goal correctly) // ok
	// free(mlx);
	// mlx_destroy_display();
	// mlx_destory_image();
	// *refer to repo of rnakatan
// 	mlx_xpm_file_to_image() == NULL // ok
// if error is occured, just check a object has been already got // ok
// if mlx occurs error, handle the error // ok
// return status // ok

// leaks in error_handling func // ok
// check_args (test.ber.e) // ok
// close(fd)
// mlx_linux doesnt work
