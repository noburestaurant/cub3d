/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 04:42:38 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			*error_msg = ft_strdup("Invalid color format");
			break;
		}
		
		// 数値以外の文字がないかチェック
		int j = 0;
		while (parts[i][j])
		{
			if (!ft_isdigit(parts[i][j]))
			{
				valid = 0;
				*error_msg = ft_strdup("Invalid color format");
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
			*error_msg = ft_strdup("Color value out of range");
			break;
		}
		i++;
	}

	if (i != 3 || parts[3] != NULL)
	{
		valid = 0;
		if (!*error_msg)
		{
			*error_msg = ft_strdup("Invalid color format");
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
		*error_msg = ft_strdup("Invalid texture file format");
		return (0);
	}
	
	// ファイルの存在チェック
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		*error_msg = ft_strdup("Texture file not found");
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
			*error_msg = ft_strdup("Duplicate identifier");
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
			*error_msg = ft_strdup("Duplicate identifier");
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
			*error_msg = ft_strdup("Duplicate identifier");
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
			*error_msg = ft_strdup("Duplicate identifier");
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
			*error_msg = ft_strdup("Duplicate identifier");
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
			*error_msg = ft_strdup("Duplicate identifier");
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
			*invalid_char = line[i]; // necessary ?
			*pos = i; // necessary ?
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
static int is_map_enclosed(char **map, int height, int width)
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
					return (0); // 境界に接していれば囲まれていない
				
				// 上下左右のマスが壁または有効なマスかチェック (スペースまたは '*' は無効)
				if (map[i-1][j] == ' ' || map[i-1][j] == '*' ||
					map[i+1][j] == ' ' || map[i+1][j] == '*' ||
					map[i][j-1] == ' ' || map[i][j-1] == '*' ||
					map[i][j+1] == ' ' || map[i][j+1] == '*')
					return (0);
			}
		}
	}
	return (1);
}

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

static void initialize_config(t_vars *vars)
{
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
}

static int	validate_all_configs(t_vars *vars)
{
	if (!vars->config.has_no || !vars->config.has_so ||
		!vars->config.has_we || !vars->config.has_ea ||
		!vars->config.has_floor || !vars->config.has_ceil)
		return (0);
	return (1);
}

static char **allocate_raw_map(void)
{
	char **raw_map;

	raw_map = (char **)malloc(sizeof(char *) * 1000);
	return (raw_map);
}

static void process_first_map_line(t_vars *vars, char *line, t_parse_data *data)
{
	char	invalid_char;
	int		invalid_pos;
	
	if (is_valid_map_line(line, &invalid_char, &invalid_pos))
	{
		data->raw_map[data->height] = ft_strdup(line);
		if (ft_strlen(line) > (size_t)data->max_width)
			data->max_width = ft_strlen(line);
		data->height++;
	}
    else
        error_message_and_free(vars, "Invalid character in map", 1); 
}

static void start_map_section(char *line, t_parse_data *data, t_vars *vars)
{
	if (!validate_all_configs(vars))
		error_message_and_free(vars, "Missing required element", 1);
	data->raw_map = allocate_raw_map();
	if (!data->raw_map)
		error_message_and_free(vars, "Memory allocation failed", 1);
	process_first_map_line(vars, line, data);
}

static void handle_config_error(char *line, int fd, t_vars *vars, char *error_msg)
{
	free(line);
	close(fd);
	error_message_and_free(vars, error_msg, 1);
}

void process_not_map_line(t_vars *vars, char *line, t_parse_data *data, int fd)
{
	if (parse_config_line(line, &vars->config, &data->error_msg) == 0)
	{
		start_map_section(line, data , vars);
		data->in_map_section = 1;
	}
	else if (data->error_msg)
		handle_config_error(line, fd, vars, data->error_msg);
}

static void handle_map_line(char *line, t_parse_data *data)
{
	if (ft_strlen(line) > 0)
	{
		data->raw_map[data->height] = ft_strdup(line);
		if (ft_strlen(line) > (size_t)data->max_width)
			data->max_width = ft_strlen(line);
		data->height++;
	}
}

void process_map_line(t_vars *vars, char *line, t_parse_data *data)
{
	char    invalid_char;
    int     invalid_pos;
                                                                               
    if (ft_strlen(line) == 0 || is_valid_map_line(line, &invalid_char, &invalid_pos))
    {   
        if (ft_strlen(line) == 0 && data->height > 0)
            error_message_and_free(vars, "Map should not have an empty line", 1);
        if (ft_strlen(line) > 0)
            handle_map_line(line, data);
    }   
    else
        error_message_and_free(vars, "Invalid character in map", 1); 
}

static void handle_empty_line(char *line, int in_map_section, t_vars *vars)
{
	free(line);
	if (in_map_section)
		error_message_and_free(vars, "Map should not have an empty line", 1);
}

static void	parse_file_content(int fd, t_vars *vars, t_parse_data *data)
{
	char	*line;

	data->in_map_section = 0;
	data->height = 0;
	data->max_width = 0;
	line = get_next_line(fd);
	while(line)
	{
		if (line[0] == '\n')
			handle_empty_line(line, data->in_map_section, vars);
		else
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			if (!data->in_map_section)
				process_not_map_line(vars, line, data, fd);
			else
				process_map_line(vars, line, data);
			free(line);
		}
		line = get_next_line(fd);
	}
}

static void cleanup_raw_map(char **raw_map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(raw_map[i]);
		i++;
	}
	free(raw_map);
}

static void validate_final_map(t_vars *vars, t_parse_data *data)
{
	int	player_count;
	int	i;

	player_count = 0;
	if (!validate_player_position(vars->map, data->height, data->max_width, &player_count))
	{
		i = 0;
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
		vars->map = NULL;
		if (player_count == 0)
			error_message_and_free(vars, "No player starting position", 1);
		else
			error_message_and_free(vars, "Multiple player starting positions", 1);
	}
	if (!is_map_enclosed(vars->map, data->height, data->max_width))
	{
		i = 0;
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
		vars->map = NULL;
		error_message_and_free(vars, "Map is not surrounded by walls", 1);
	}
}

static void finalize_parsing(t_vars *vars, t_parse_data *data)
{
	if (data->height == 0)
		error_message_and_free(vars, "Missing required element", 1);
	data->raw_map[data->height] = NULL;
	vars->map = adjust_map_data(data->raw_map, data->height, data->max_width);
	cleanup_raw_map(data->raw_map, data->height);
	if (!vars->map)
		error_message_and_free(vars, "Momory allocation failed", 1);
	validate_final_map(vars, data);
	vars->height = data->height;
	vars->width = data->max_width;
}

static void parse_cub_file(char *file_path, t_vars *vars)
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

void validation_and_parse(int argc, char **argv, t_vars *vars)
{
	if (argc != 2)
		error_message_and_free(vars, "Invalid number of arguments", 1);
	if (!is_valid_extension(argv[1]))
		error_message_and_free(vars, "Invalid file name", 1);
	parse_cub_file(argv[1], vars);
	parse_map(vars);
}

// validation_and_parse()
	// メイン検証・解析関数
	// 引数の数をチェック
	// ファイル拡張子のチェック
	// ファイルの解析
	// プレイヤーの向きと位置を取得
