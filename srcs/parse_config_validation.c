/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:29:14 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:18:02 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_all_configs(t_vars *vars)
{
	if (!vars->config.has_no || !vars->config.has_so
		|| !vars->config.has_we || !vars->config.has_ea
		|| !vars->config.has_floor || !vars->config.has_ceil)
		return (0);
	return (1);
}

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

int	validate_color_count(char **parts, char **error_msg)
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

int	check_digit_only(char *str)
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

int	validate_color_value(char *part, int *color_val, char **error_msg)
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
