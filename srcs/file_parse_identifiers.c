/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_identifiers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 04:46:41 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
