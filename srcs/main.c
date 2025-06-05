/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:00:37 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 13:33:09 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_handle_error(char *crr_line, char *linked_lines)
{
	if (crr_line != NULL && crr_line[0] == '\n')
	{
		free(linked_lines);
		free(crr_line);
		error_message_and_free(NULL, "Invalid character in map", 1);
	}
	if (linked_lines[0] == '\0')
	{
		free(linked_lines);
		free(crr_line);
		error_message_and_free(NULL, "Missing required element", 1);
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
		error_message_and_free(NULL, "Cannot open file", 1);
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

void	init_vars(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->img_renga = NULL;
	vars->img_grass = NULL;
	vars->img_player = calloc(1, sizeof(t_vars) * 1);
	if (vars->img_player == NULL)
		exit (1);
	vars->map = NULL;
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_vars(&vars);
	validation_and_parse(argc, argv, &vars);
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		error_message_and_free(&vars, "Unexpected Error: mlx\n", 1);
	vars.win = mlx_new_window(vars.mlx, vars.width * 50,
			vars.height * 50, "game");
	if (vars.win == NULL)
		error_message_and_free(&vars, "Unexpected Error: mlx\n", 1);
	get_img(&vars);
	render_map(&vars);
	print_player(&vars);
	render_rays(&vars);
	print_orientation(&vars);
	render_field_of_view(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, window_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

// 無効なマップ
// マップが'1'で囲まれていない場合
// '0', '1'以外の文字を含む空間の描画、またはプレイヤーがそこに移動する場合
// 'N', 'S', 'W', 'E' が複数存在する場合（プレイヤーのスポーン位置は1つのみ）

// マップ実装詳細
// map の1行目と最後の行が'1'または' 'で構成されていること
// 各行のの左右の端が'1'である
// '0'およびプレイヤーのスポーン地点（N, S, E, W）の周囲8方向に<space>, <tab>が存在しないこと
// 	この際、対象行のn番目の文字が前後の行より大きい場合、壁に囲まれていないとみなす？

// 床と天井の色の指定
// 床と天井の色は、課題要件に基づき特定の色で指定されますが、テクスチャでの描画も可能
// 解析時に、床と天井が色指定かテクスチャパスしていかを認識する
// 'F'か'C'の後の文字列が数字で構成されている場合、色指定とみなす
// 	RGBの3つの値を構造体に代入する
// テクスチャ指定の場合は、'N', 'S', 'E', 'W'の指定と同様の処理を行う