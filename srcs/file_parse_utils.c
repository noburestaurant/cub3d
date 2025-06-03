/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/03 14:00:00 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ファイル拡張子が.cubかどうかをチェック
int	is_valid_extension(char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (ft_strnstr(&filename[len - 4], ".cub", 4) != NULL);
}

static int	check_color_parts(char **parts, int color[3], char **error_msg)
{
	int	i;
	int	j;

	i = 0;
	while (parts[i] && i < 3)
	{
		if (!parts[i] || !ft_isdigit(parts[i][0]))
		{
			*error_msg = ft_strdup("Invalid color format");
			return (0);
		}
		j = 0;
		while (parts[i][j])
		{
			if (!ft_isdigit(parts[i][j]))
			{
				*error_msg = ft_strdup("Invalid color format");
				return (0);
			}
			j++;
		}
		color[i] = ft_atoi(parts[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			*error_msg = ft_strdup("Color value out of range");
			return (0);
		}
		i++;
	}
	return (1);
}

// 色表記（R,G,B）が有効かチェック
int	is_valid_color_format(char *color_str, int color[3], char **error_msg)
{
	char	**parts;
	int		i;
	int		valid;

	parts = ft_split(color_str, ',');
	if (!parts)
		return (0);
	valid = check_color_parts(parts, color, error_msg);
	if (valid && (parts[3] != NULL || i != 3))
	{
		valid = 0;
		if (!*error_msg)
			*error_msg = ft_strdup("Invalid color format");
	}
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
int	is_valid_texture_path(char *path, char **error_msg)
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

// 識別子の種類を特定する（NO, SO, WE, EA, F, C）
int	get_identifier_type(char *line)
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
