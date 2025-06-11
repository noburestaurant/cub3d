/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:45:41 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 13:46:12 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_empty_line(char *line, int in_map_section, t_vars *vars)
{
	free(line);
	if (in_map_section)
		error_message_and_free(vars, "Map should not have an empty line", 1);
}
