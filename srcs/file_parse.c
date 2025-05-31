/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/05/31 14:38:27 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ファイル拡張子が.cubかどうかをチェック
static int is_valid_extension(char *filename)
{
	size_t len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5) // .cub で最低4文字必要
		return (0);
	return (ft_strnstr(&filename[len - 4], ".cub", 4) != NULL);
}

// 色表記（R,G,B）が有効かチェック
static int is_valid_color_format(char *color_str, int color[3], char **error_msg)
{
	char	**parts;
	int		i;
	int		valid;

	parts = ft_split(color_str, ',');
	if (!parts)
		return (0);
	
	i = 0;
	valid = 1;
	while (parts[i] && i < 3)
	{
		// 各色値が数値であり、0～255の範囲内かチェック
		if (!parts[i] || !ft_isdigit(parts[i][0]))
		{
			valid = 0;
			*error_msg = ft_strdup("Invalid color format: ");
			*error_msg = ft_strjoin(*error_msg, color_str);
			break;
		}
		
		// 数値以外の文字がないかチェック
		int j = 0;
		while (parts[i][j])
		{
			if (!ft_isdigit(parts[i][j]))
			{
				valid = 0;
				*error_msg = ft_strdup("Invalid color format: ");
				*error_msg = ft_strjoin(*error_msg, color_str);
				break;
			}
			j++;
		}
		if (!valid)
			break;
			
		color[i] = ft_atoi(parts[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			valid = 0;
			*error_msg = ft_strdup("Color value out of range: ");
			char num_str[4];
			snprintf(num_str, sizeof(num_str), "%d", color[i]);
			*error_msg = ft_strjoin(*error_msg, num_str);
			break;
		}
		i++;
	}

	if (i != 3 || parts[3] != NULL)
	{
		valid = 0;
		if (!*error_msg)
		{
			*error_msg = ft_strdup("Invalid color format: ");
			*error_msg = ft_strjoin(*error_msg, color_str);
		}
	}

	// 分割した文字列の解放
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
	return (valid);
}

// テクスチャファイルが存在し、XPM形式かチェック
static int is_valid_texture_path(char *path, char **error_msg)
{
	size_t	len;
	int		fd;

	if (!path)
		return (0);
	
	len = ft_strlen(path);
	if (len < 5) // 最低でも .xpm で4文字必要
		return (0);
	
	// .xpm 拡張子チェック
	if (ft_strnstr(&path[len - 4], ".xpm", 4) == NULL)
	{
		*error_msg = ft_strdup("Invalid texture file format (must be .xpm): ");
		*error_msg = ft_strjoin(*error_msg, path);
		return (0);
	}
	
	// ファイルの存在チェック
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		*error_msg = ft_strdup("Texture file not found: ");
		*error_msg = ft_strjoin(*error_msg, path);
		return (0);
	}
	close(fd);
	
	return (1);
}

// 識別子の種類を特定する（NO, SO, WE, EA, F, C）
static int get_identifier_type(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (-1);
	
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (0); // NO
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (1); // SO
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (2); // WE
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (3); // EA
	else if (line[0] == 'F' && line[1] == ' ')
		return (4); // F
	else if (line[0] == 'C' && line[1] == ' ')
		return (5); // C
	
	return (-1); // 不明な識別子
}

// 設定項目の解析処理
static int parse_config_line(char *line, t_config *config, char **error_msg)
{
	int		type;
	char	*value;
	
	type = get_identifier_type(line);
	if (type == -1)
		return (0); // 有効な識別子でない場合はマップの開始と判断
	
	// 識別子の後の値部分を取得
	if (type <= 3) // NO, SO, WE, EA
		value = ft_strtrim(line + 3, " \t\n\r\v\f");
	else // F, C
		value = ft_strtrim(line + 2, " \t\n\r\v\f");
	
	if (!value)
		return (-1);
	
	// 識別子ごとの処理
	if (type == 0) // NO
	{
		if (config->has_no)
		{
			*error_msg = ft_strdup("Duplicate identifier: NO");
			free(value);
			return (-1);
		}
		if (!is_valid_texture_path(value, error_msg))
		{
			free(value);
			return (-1);
		}
		config->no_path = value;
		config->has_no = 1;
	}
	else if (type == 1) // SO
	{
		if (config->has_so)
		{
			*error_msg = ft_strdup("Duplicate identifier: SO");
			free(value);
			return (-1);
		}
		if (!is_valid_texture_path(value, error_msg))
		{
			free(value);
			return (-1);
		}
		config->so_path = value;
		config->has_so = 1;
	}
	else if (type == 2) // WE
	{
		if (config->has_we)
		{
			*error_msg = ft_strdup("Duplicate identifier: WE");
			free(value);
			return (-1);
		}
		if (!is_valid_texture_path(value, error_msg))
		{
			free(value);
			return (-1);
		}
		config->we_path = value;
		config->has_we = 1;
	}
	else if (type == 3) // EA
	{
		if (config->has_ea)
		{
			*error_msg = ft_strdup("Duplicate identifier: EA");
			free(value);
			return (-1);
		}
		if (!is_valid_texture_path(value, error_msg))
		{
			free(value);
			return (-1);
		}
		config->ea_path = value;
		config->has_ea = 1;
	}
	else if (type == 4) // F
	{
		if (config->has_floor)
		{
			*error_msg = ft_strdup("Duplicate identifier: F");
			free(value);
			return (-1);
		}
		if (!is_valid_color_format(value, config->floor_color, error_msg))
		{
			free(value);
			return (-1);
		}
		free(value);
		config->has_floor = 1;
	}
	else if (type == 5) // C
	{
		if (config->has_ceil)
		{
			*error_msg = ft_strdup("Duplicate identifier: C");
			free(value);
			return (-1);
		}
		if (!is_valid_color_format(value, config->ceil_color, error_msg))
		{
			free(value);
			return (-1);
		}
		free(value);
		config->has_ceil = 1;
	}
	
	return (1);
}

// マップの一行が有効かチェック
static int is_valid_map_line(char *line, char *invalid_char, int *pos)
{
	int i;

	if (!line)
		return (0);

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			*invalid_char = line[i];
			*pos = i;
			return (0);
		}
		i++;
	}
	return (1);
}

// マップデータを調整（各行の長さを最大幅に合わせて'*'で埋める）
static char **adjust_map_data(char **raw_map, int height, int width)
{
	char	**adjusted_map;
	int		i;
	int		j;
	int		len;

	adjusted_map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!adjusted_map)
		return (NULL);
	
	i = 0;
	while (i < height)
	{
		adjusted_map[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!adjusted_map[i])
		{
			while (--i >= 0)
				free(adjusted_map[i]);
			free(adjusted_map);
			return (NULL);
		}
		
		// 元のマップデータをコピー
		j = 0;
		len = ft_strlen(raw_map[i]);
		while (j < len)
		{
			adjusted_map[i][j] = raw_map[i][j];
			j++;
		}
		
		// 余った部分を'*'で埋める
		while (j < width)
		{
			adjusted_map[i][j] = '*';
			j++;
		}
		adjusted_map[i][width] = '\0';
		i++;
	}
	adjusted_map[height] = NULL;
	
	return (adjusted_map);
}

// マップが壁で完全に囲まれているかチェック
static int is_map_enclosed(char **map, int height, int width, int error_pos[2])
{
	int i;
	int j;
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || 
				map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				// 上下左右の境界チェック
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
				{
					error_pos[0] = j;
					error_pos[1] = i;
					return (0); // 境界に接していれば囲まれていない
				}
				
				// 上下左右のマスが壁または有効なマスかチェック (スペースまたは '*' は無効)
				if (map[i-1][j] == ' ' || map[i-1][j] == '*' ||
					map[i+1][j] == ' ' || map[i+1][j] == '*' ||
					map[i][j-1] == ' ' || map[i][j-1] == '*' ||
					map[i][j+1] == ' ' || map[i][j+1] == '*')
				{
					error_pos[0] = j;
					error_pos[1] = i;
					return (0);
				}
			}
		}
	}
	return (1);
}

// プレイヤーの位置を特定し、有効性をチェック
static int validate_player_position(char **map, int height, int width, int *player_count)
{
	int i;
	int j;
	*player_count = 0;
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || 
				map[i][j] == 'E' || map[i][j] == 'W')
				(*player_count)++;
		}
	}
	
	return (*player_count == 1);
}

// .cubファイルを解析し、設定とマップデータを取得する
static int parse_cub_file(char *file_path, t_vars *vars)
{
	int		fd;
	char	*line;
	int		ret;
	int		in_map_section = 0;
	int		height = 0;
	int		max_width = 0;
	char	**raw_map = NULL;
	char	*error_msg = NULL;
	
	// 初期化
	vars->config.has_no = 0;
	vars->config.has_so = 0;
	vars->config.has_we = 0;
	vars->config.has_ea = 0;
	vars->config.has_floor = 0;
	vars->config.has_ceil = 0;
	vars->config.no_path = NULL;
	vars->config.so_path = NULL;
	vars->config.we_path = NULL;
	vars->config.ea_path = NULL;
	
	// ファイルオープン
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	
	// 一行ずつ読み込み
	while ((line = get_next_line(fd)))
	{
		// 空行のスキップ
		if (line[0] == '\n')
		{
			free(line);
			if (in_map_section) // マップセクション内の空行はエラー
			{
				if (height > 0) // マップの最初の行より後の空行
					error_message_and_free(vars, "Map contains empty line", 1);
			}
			continue;
		}
		
		// 改行を除去
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		
		// マップセクション以外での処理
		if (!in_map_section)
		{
			ret = parse_config_line(line, &vars->config, &error_msg);
			if (ret == -1) // 設定エラー
			{
				free(line);
				close(fd);
				if (error_msg)
				{
					error_message_and_free(vars, error_msg, 1);
					free(error_msg);
				}
				return (0);
			}
			else if (ret == 0) // マップセクションの開始
			{
				if (!vars->config.has_no || !vars->config.has_so ||
					!vars->config.has_we || !vars->config.has_ea ||
					!vars->config.has_floor || !vars->config.has_ceil)
				{
					free(line);
					close(fd);
					return (0); // 必須要素の不足
				}
				
				in_map_section = 1;
				
				// マップの最初の行を処理
				char invalid_char;
				int invalid_pos;
				if (is_valid_map_line(line, &invalid_char, &invalid_pos))
				{
					raw_map = (char **)malloc(sizeof(char *) * 1000); // 仮に1000行とする
					if (!raw_map)
					{
						free(line);
						close(fd);
						return (0);
					}
					raw_map[height] = ft_strdup(line);
					if (ft_strlen(line) > (size_t)max_width)
						max_width = ft_strlen(line);
					height++;
				}
				else
				{
					char error_msg[100];
					snprintf(error_msg, sizeof(error_msg), "Invalid character in map: %c at position (%d,%d)", invalid_char, invalid_pos, height);
					free(line);
					close(fd);
					error_message_and_free(vars, error_msg, 1);
					return (0); // マップに無効な文字
				}
			}
		}
		else // マップセクション内
		{
			// マップ行の処理
			char invalid_char;
			int invalid_pos;
			
			// マップ行の妥当性チェック
			if (ft_strlen(line) == 0 || is_valid_map_line(line, &invalid_char, &invalid_pos))
			{
				// 空行がマップの途中に現れた場合
				if (ft_strlen(line) == 0 && height > 0)
				{
					free(line);
					close(fd);
					int i = 0;
					while (i < height)
					{
						free(raw_map[i]);
						i++;
					}
					free(raw_map);
					error_message_and_free(vars, "Map contains empty line", 1);
					return (0);
				}
				
				// 有効なマップ行を追加
				if (ft_strlen(line) > 0)
				{
					raw_map[height] = ft_strdup(line);
					if (ft_strlen(line) > (size_t)max_width)
						max_width = ft_strlen(line);
					height++;
				}
			}
			else
			{
				// マップデータ後の追加の設定行や無効な文字をチェック
				if (get_identifier_type(line) != -1)
				{
					free(line);
					close(fd);
					int i = 0;
					while (i < height)
					{
						free(raw_map[i]);
						i++;
					}
					free(raw_map);
					error_message_and_free(vars, "Content after map", 1);
					return (0);
				}
				else
				{
					char error_msg[100];
					snprintf(error_msg, sizeof(error_msg), "Invalid character in map: %c at position (%d,%d)", invalid_char, invalid_pos, height);
					free(line);
					close(fd);
					// マップ行の解放
					int i = 0;
					while (i < height)
					{
						free(raw_map[i]);
						i++;
					}
					free(raw_map);
					error_message_and_free(vars, error_msg, 1);
					return (0); // マップに無効な文字
				}
			}
		}
		
		free(line);
	}
	
	close(fd);
	
	if (!in_map_section || height == 0)
		return (0); // マップなし
	
	raw_map[height] = NULL;
	
	// マップの調整
	vars->map = adjust_map_data(raw_map, height, max_width);
	
	// raw_map の解放
	int i = 0;
	while (i < height)
	{
		free(raw_map[i]);
		i++;
	}
	free(raw_map);
	
	if (!vars->map)
		return (0);
	
	// マップのバリデーション
	int player_count = 0;
	if (!validate_player_position(vars->map, height, max_width, &player_count))
	{
		i = 0;
		while (vars->map[i])
		{
			free(vars->map[i]);
			i++;
		}
		free(vars->map);
		vars->map = NULL;
		if (player_count == 0)
			error_message_and_free(vars, "No player starting position", 1);
		else
			error_message_and_free(vars, "Multiple player starting positions", 1);
		return (0); // プレイヤー位置が不正
	}

	int error_pos[2] = {0, 0};
	if (!is_map_enclosed(vars->map, height, max_width, error_pos))
	{
		i = 0;
		while (vars->map[i])
		{
			free(vars->map[i]);
			i++;
		}
		free(vars->map);
		vars->map = NULL;
		char error_msg[100];
		snprintf(error_msg, sizeof(error_msg), "Map is not surrounded by walls at position (%d,%d)", error_pos[0], error_pos[1]);
		error_message_and_free(vars, error_msg, 1);
		return (0); // マップが壁で囲まれていない
	}
	
	vars->height = height;
	vars->width = max_width;
	
	return (1);
}

// メイン検証・解析関数
void validation_and_parse(int argc, char **argv, t_vars *vars)
{
	// 引数の数をチェック
	if (argc != 2)
		error_message_and_free(vars, "Invalid number of arguments", 1);
	
	// ファイル拡張子のチェック
	if (!is_valid_extension(argv[1]))
		error_message_and_free(vars, "Invalid file name", 1);
	
	// ファイルの解析
	if (!parse_cub_file(argv[1], vars))
	{
		// エラーメッセージ
		if (!vars->config.has_no)
			error_message_and_free(vars, "Missing required element: NO", 1);
		else if (!vars->config.has_so)
			error_message_and_free(vars, "Missing required element: SO", 1);
		else if (!vars->config.has_we)
			error_message_and_free(vars, "Missing required element: WE", 1);
		else if (!vars->config.has_ea)
			error_message_and_free(vars, "Missing required element: EA", 1);
		else if (!vars->config.has_floor)
			error_message_and_free(vars, "Missing required element: F", 1);
		else if (!vars->config.has_ceil)
			error_message_and_free(vars, "Missing required element: C", 1);
		else if (!vars->map)
			error_message_and_free(vars, "No map in file", 1);
		else
			error_message_and_free(vars, "Unknown error during file parsing", 1);
	}
	
	// プレイヤーの向きと位置を取得
	parse_map(vars);
}
