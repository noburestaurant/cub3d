/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:22:21 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cub_file(char *file_path, t_vars *vars)
{
	int				fd;
	t_parse_data	data;

	initialize_config(vars);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_message_and_free(vars, "Cannot open file", 1);
	parse_file_content(fd, vars, &data);
	close(fd);
	finalize_parsing(vars, &data);
}

void	validation_and_parse(int argc, char **argv, t_vars *vars)
{
	if (argc != 2)
		error_message_and_free(vars, "Invalid number of arguments", 1);
	if (!is_valid_extension(argv[1]))
		error_message_and_free(vars, "Invalid file name", 1);
	parse_cub_file(argv[1], vars);
}

// validation_and_parse()
	// メイン検証・解析関数
	// 引数の数をチェック
	// ファイル拡張子のチェック
	// ファイルの解析
	// プレイヤーの向きと位置を取得
