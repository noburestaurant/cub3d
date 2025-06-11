/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 09:22:16 hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_color_count(char **parts, char **error_msg)
{
	int	count;
	
	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
	{
		*error_msg = ft_strdup("Invalid color format");
		return (0);
	}
	return (1);
}

static int	check_digit_only(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int validate_color_value(char *part, int *color_val, char **error_msg)
{
	if (!check_digit_only(part))
	{
		*error_msg = ft_strdup("Invalid color format");
		return (0);
	}
	*color_val = ft_atoi(part);
	if (*color_val < 0 || *color_val > 255)
	{
		*error_msg = ft_strdup("Color value out of range");
		return (0);
	}
	return (1);
}

static void free_color_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static int is_valid_color_format(char *color_str, int color[3],
		char **error_msg)
{
	char	**parts;
	int		i;

	parts = ft_split(color_str, ',');
	if (!parts)
		return (0); // enough to indicate an error ?
	if (!validate_color_count(parts, error_msg))
	{
		free_color_parts(parts);
		return (0); // enough to indicate an error ?
	}
	i = 0;
	while (i < 3)
	{
		if (!validate_color_value(parts[i], &color[i], error_msg))
		{
			free_color_parts(parts);
			return (0);
		}
		i++;
	}
	free_color_parts(parts);
	return (1);

	// i = 0;
	// valid = 1;
	// while (parts[i] && i < 3)
	// {
	// 	// 各色値が数値であり、0～255の範囲内かチェック
	// 	if (!parts[i] || !ft_isdigit(parts[i][0]))
	// 	{
	// 		valid = 0;
	// 		*error_msg = ft_strdup("Invalid color format");
	// 		break;
	// 	}
		
	// 	// 数値以外の文字がないかチェック
	// 	int j = 0;
	// 	while (parts[i][j])
	// 	{
	// 		if (!ft_isdigit(parts[i][j]))
	// 		{
	// 			valid = 0;
	// 			*error_msg = ft_strdup("Invalid color format");
	// 			break;
	// 		}
	// 		j++;
	// 	}
	// 	if (!valid)
	// 		break;
			
	// 	color[i] = ft_atoi(parts[i]);
	// 	if (color[i] < 0 || color[i] > 255)
	// 	{
	// 		valid = 0;
	// 		*error_msg = ft_strdup("Color value out of range");
	// 		break;
	// 	}
	// 	i++;
	// }

	// if (i != 3 || parts[3] != NULL)
	// {
	// 	valid = 0;
	// 	if (!*error_msg)
	// 	{
	// 		*error_msg = ft_strdup("Invalid color format");
	// 	}
	// }

	// // 分割した文字列の解放
	// i = 0;
	// while (parts[i])
	// {
	// 	free(parts[i]);
	// 	i++;
	// }
	// free(parts);
	// return (valid);
}

static int	is_valid_texture_path(char *path, char **error_msg)
{
	size_t	len;
	int		fd;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strnstr(&path[len - 4], ".xpm", 4) == NULL)
	{
		*error_msg = ft_strdup("Invalid texture file format");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		*error_msg = ft_strdup("Texture file not found");
		return (0);
	}
	close(fd);
	return (1);
}

static int	handle_duplicate_config(int has_config, char **error_msg, char *value)
{
	if (has_config)
	{
		*error_msg = ft_strdup("Duplicate identifier");
		free(value);
		return (-1);
	}
	return (0);
}

static int	process_texture_config(char *value, char **path, char **error_msg)
{
	if (!is_valid_texture_path(value, error_msg))
	{
		free(value);
			return (-1);
	}
	*path = value;
	return (1);
}

static int	process_color_config(char *value, int *color, char **error_msg)
{
	if (!is_valid_color_format(value, color, error_msg))
	{
		free(value);
		return (-1);
	}
	free(value);
	return (1);
}

static int	handle_no_config(t_config *config, char *value, char **error_msg)
{
	if (handle_duplicate_config(config->has_no, error_msg, value) == -1)
		return (-1);
	if (process_texture_config(value, &config->no_path, error_msg) == -1)
		return (-1);
	config->has_no = 1;
	return (1);
}

static int	handle_so_config(t_config *config, char *value, char **error_msg)
{
    if (handle_duplicate_config(config->has_so, error_msg, value) == -1)
        return (-1);
    if (process_texture_config(value, &config->so_path, error_msg) == -1)
        return (-1);
    config->has_so = 1;
    return (1);
}

static int	handle_we_config(t_config *config, char *value, char **error_msg)
{
    if (handle_duplicate_config(config->has_we, error_msg, value) == -1)
        return (-1);
    if (process_texture_config(value, &config->we_path, error_msg) == -1)
        return (-1);
    config->has_we = 1;
    return (1);
}

static int	handle_ea_config(t_config *config, char *value, char **error_msg)
{
    if (handle_duplicate_config(config->has_ea, error_msg, value) == -1)
        return (-1);
    if (process_texture_config(value, &config->ea_path, error_msg) == -1)
        return (-1);
    config->has_ea = 1;
    return (1);
}

static int	handle_floor_config(t_config *config, char *value, char **error_msg)
{
    if (handle_duplicate_config(config->has_floor, error_msg, value) == -1)
        return (-1);
    if (process_color_config(value, config->floor_color, error_msg) == -1)
        return (-1);
    config->has_floor = 1;
    return (1);
}

static int	handle_ceil_config(t_config *config, char *value, char **error_msg)
{
    if (handle_duplicate_config(config->has_ceil, error_msg, value) == -1)
        return (-1);
    if (process_color_config(value, config->ceil_color, error_msg) == -1)
        return (-1);
    config->has_ceil = 1;
    return (1);
}

static int	get_identifier_type(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (-1);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (0);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (1);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (2);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (3);
	else if (line[0] == 'F' && line[1] == ' ')
		return (4);
	else if (line[0] == 'C' && line[1] == ' ')
		return (5);
	return (-1);
}

static char	*get_config_value(char *line, int type)
{
	char	*value;

	if (type <= 3)
		value = ft_strtrim(line + 3, " \t\n\r\v\f"); // valid "F 200,   200 ,   200" ?
	else
		value = ft_strtrim(line + 2, " \t\n\r\v\f");
	return (value);
}

static int	process_config_by_type(t_config *config, int type, char *value, char **error_msg)
{
	if (type == 0)
		return (handle_no_config(config, value, error_msg));
	else if (type == 1)
		return (handle_so_config(config, value, error_msg));
	else if (type == 2)
		return (handle_we_config(config, value, error_msg));
	else if (type == 3)
		return (handle_ea_config(config, value, error_msg));
	else if (type == 4)
		return (handle_floor_config(config, value, error_msg));
	else if (type == 5)
		return (handle_ceil_config(config, value, error_msg));
	return (-1); // enough to indicate an error ?
}

// 全部揃ったと思われるときに 0 を返す // エラーのときはmsgをセットする
static int	parse_config_line(char *line, t_config *config, char **error_msg)
{
	int		type;
	char	*value;
	
	type = get_identifier_type(line);
	if (type == -1)
		return (0);
	value = get_config_value(line, type);
	if (!value) // why not to set error_msg here?
		return (-1);
	return (process_config_by_type(config, type, value, error_msg));
	
	// // 識別子の後の値部分を取得
	// if (type <= 3) // NO, SO, WE, EA
	// 	value = ft_strtrim(line + 3, " \t\n\r\v\f");
	// else // F, C
	// 	value = ft_strtrim(line + 2, " \t\n\r\v\f");
	
	// if (!value)
	// 	return (-1);
	
	// // 識別子ごとの処理
	// if (type == 0) // NO
	// {
	// 	if (config->has_no)
	// 	{
	// 		*error_msg = ft_strdup("Duplicate identifier");
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	if (!is_valid_texture_path(value, error_msg))
	// 	{
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	config->no_path = value;
	// 	config->has_no = 1;
	// }
	// else if (type == 1) // SO
	// {
	// 	if (config->has_so)
	// 	{
	// 		*error_msg = ft_strdup("Duplicate identifier");
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	if (!is_valid_texture_path(value, error_msg))
	// 	{
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	config->so_path = value;
	// 	config->has_so = 1;
	// }
	// else if (type == 2) // WE
	// {
	// 	if (config->has_we)
	// 	{
	// 		*error_msg = ft_strdup("Duplicate identifier");
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	if (!is_valid_texture_path(value, error_msg))
	// 	{
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	config->we_path = value;
	// 	config->has_we = 1;
	// }
	// else if (type == 3) // EA
	// {
	// 	if (config->has_ea)
	// 	{
	// 		*error_msg = ft_strdup("Duplicate identifier");
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	if (!is_valid_texture_path(value, error_msg))
	// 	{
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	config->ea_path = value;
	// 	config->has_ea = 1;
	// }
	// else if (type == 4) // F
	// {
	// 	if (config->has_floor)
	// 	{
	// 		*error_msg = ft_strdup("Duplicate identifier");
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	if (!is_valid_color_format(value, config->floor_color, error_msg))
	// 	{
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	free(value);
	// 	config->has_floor = 1;
	// }
	// else if (type == 5) // C
	// {
	// 	if (config->has_ceil)
	// 	{
	// 		*error_msg = ft_strdup("Duplicate identifier");
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	if (!is_valid_color_format(value, config->ceil_color, error_msg))
	// 	{
	// 		free(value);
	// 		return (-1);
	// 	}
	// 	free(value);
	// 	config->has_ceil = 1;
	// }
	
	// return (1);
}

static int	is_valid_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

char	**alloc_two_dimensional_array(int height, int width)
{
	char	**arrays;
	int		i;

	i = 0;
	arrays = (char **)malloc(sizeof(char *) * (height + 1));
	if (!arrays)
		return (NULL);
	i = 0;
	while (i < height)
	{
		arrays[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!arrays[i])
		{
			while (--i >= 0)
				free(arrays[i]);
			free(arrays);
			return (NULL);
		}
		arrays[i][width] = '\0';
		i++;
	}
	arrays[height] = NULL;
	return (arrays);
}

static char	**adjust_map_data(char **raw_map, int height, int width)
{
	char	**adjusted_map;
	int		i;
	int		j;
	int		len;

	adjusted_map = alloc_two_dimensional_array(height, width);
	if (!adjusted_map)
		return (NULL);
	i = -1;
	while (++i < height)
	{
		j = -1;
		len = ft_strlen(raw_map[i]);
		while (++j < len)
		{
			if (raw_map[i][j] != ' ')
				adjusted_map[i][j] = raw_map[i][j];
			else
				adjusted_map[i][j] = '*';
		}
		while (++j < width)
			adjusted_map[i][j] = '*';
	}
	return (adjusted_map);
}

static int	is_map_enclosed(char **map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
					return (0);
				if (map[i - 1][j] == ' ' || map[i - 1][j] == '*'
					|| map[i + 1][j] == ' ' || map[i + 1][j] == '*'
					|| map[i][j - 1] == ' ' || map[i][j - 1] == '*'
					|| map[i][j + 1] == ' ' || map[i][j + 1] == '*')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	validate_player_position(char **map, int height,
		int width, int *player_count)
{
	int	i;
	int	j;

	*player_count = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				(*player_count)++;
			j++;
		}
		i++;
	}
	return (*player_count == 1);
}

static void	initialize_config(t_vars *vars)
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
	if (!vars->config.has_no || !vars->config.has_so
		|| !vars->config.has_we || !vars->config.has_ea
		|| !vars->config.has_floor || !vars->config.has_ceil)
		return (0);
	return (1);
}

static char	**allocate_raw_map(void)
{
	char	**raw_map;

	raw_map = (char **)malloc(sizeof(char *) * 1000);
	return (raw_map);
}

static void	process_first_map_line(t_vars *vars, char *line,
		t_parse_data *data)
{
	if (is_valid_map_line(line))
	{
		data->raw_map[data->height] = ft_strdup(line);
		if (ft_strlen(line) > (size_t)data->max_width)
			data->max_width = ft_strlen(line);
		data->height++;
	}
	else
		error_message_and_free(vars, "Invalid character in map", 1);
}

static void	start_map_section(char *line, t_parse_data *data, t_vars *vars)
{
	if (!validate_all_configs(vars))
		error_message_and_free(vars, "Missing required element", 1);
	data->raw_map = allocate_raw_map();
	if (!data->raw_map)
		error_message_and_free(vars, "Memory allocation failed", 1);
	process_first_map_line(vars, line, data);
}

static void	handle_config_error(char *line, int fd, t_vars *vars,
		char *error_msg)
{
	free(line);
	close(fd);
	error_message_and_free(vars, error_msg, 1);
}

void	process_not_map_line(t_vars *vars, char *line, t_parse_data *data,
		int fd)
{
	if (parse_config_line(line, &vars->config, &data->error_msg) == 0)
	{
		start_map_section(line, data, vars);
		data->in_map_section = 1;
	}
	else if (data->error_msg)
		handle_config_error(line, fd, vars, data->error_msg);
}

static void	handle_map_line(char *line, t_parse_data *data)
{
	if (ft_strlen(line) > 0)
	{
		data->raw_map[data->height] = ft_strdup(line);
		if (ft_strlen(line) > (size_t)data->max_width)
			data->max_width = ft_strlen(line);
		data->height++;
	}
}

void	process_map_line(t_vars *vars, char *line, t_parse_data *data)
{
	if (ft_strlen(line) == 0 || is_valid_map_line(line))
	{
		if (ft_strlen(line) == 0 && data->height > 0)
			error_message_and_free(vars,
				"Map should not have an empty line", 1);
		if (ft_strlen(line) > 0)
			handle_map_line(line, data);
	}
	else
		error_message_and_free(vars, "Invalid character in map", 1);
}

static void	handle_empty_line(char *line, int in_map_section, t_vars *vars)
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
	while (line)
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

static void	cleanup_raw_map(char **raw_map, int height)
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

static void	validate_final_map(t_vars *vars, t_parse_data *data)
{
	int	player_count;

	player_count = 0;
	if (!validate_player_position(vars->map, data->height,
			data->max_width, &player_count))
	{
		if (player_count == 0)
			error_message_and_free(vars, "No player starting position", 1);
		else
			error_message_and_free(vars,
				"Multiple player starting positions", 1);
	}
	if (!is_map_enclosed(vars->map, data->height, data->max_width))
		error_message_and_free(vars, "Map is not surrounded by walls", 1);
}

static void	finalize_parsing(t_vars *vars, t_parse_data *data)
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

static void	parse_cub_file(char *file_path, t_vars *vars)
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
	parse_map(vars);
}

// validation_and_parse()
	// メイン検証・解析関数
	// 引数の数をチェック
	// ファイル拡張子のチェック
	// ファイルの解析
	// プレイヤーの向きと位置を取得
