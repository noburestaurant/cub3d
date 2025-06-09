/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_extension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/01 16:33:10 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_valid_extension(char *filename)
{
	size_t len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	return (ft_strnstr(&filename[len - 4], ".cub", 4) != NULL);
}
