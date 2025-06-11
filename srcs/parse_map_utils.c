/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:29:21 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/11 14:22:10 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**allocate_raw_map(void)
{
	char	**raw_map;

	raw_map = (char **)malloc(sizeof(char *) * 1000);
	return (raw_map);
}
