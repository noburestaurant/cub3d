/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:05:12 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 05:22:06 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture_data(t_vars *vars, t_texture *texture, void *img,
		char *error_msg)
{
	texture->addr = mlx_get_data_addr(img, &(texture->bits_per_pixel),
			&(texture->line_length), &(texture->endian));
	if (texture->addr == NULL)
		error_message_and_free(vars, error_msg, 1);
}

void	convert_img_to_data_addr(t_vars *vars)
{
	load_texture_data(vars, &(vars->textures->texture_north),
		vars->img_player->north, "Cannot load texture");
	load_texture_data(vars, &(vars->textures->texture_south),
		vars->img_player->south, "Cannot load texture");
	load_texture_data(vars, &(vars->textures->texture_east),
		vars->img_player->east, "Cannot load texture");
	load_texture_data(vars, &(vars->textures->texture_west),
		vars->img_player->west, "Cannot load texture");
}

void	get_img(t_vars *vars)
{
	load_basic_images(vars);
	load_player_images(vars);
	vars->textures = (t_texture_list *)malloc(sizeof(t_texture_list) * 1);
	if (vars->textures == NULL)
		exit(1);
	convert_img_to_data_addr(vars);
}
