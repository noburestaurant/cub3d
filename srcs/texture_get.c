/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:05:12 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 12:19:30 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_img_to_data_addr(t_vars *vars)
{
	vars->textures->texture_north.addr = mlx_get_data_addr(
			vars->img_player->north,
			&(vars->textures->texture_north.bits_per_pixel),
			&(vars->textures->texture_north.line_length),
			&(vars->textures->texture_north.endian));
	if (vars->textures->texture_north.addr == NULL)
		exit(1);
	vars->textures->texture_south.addr = mlx_get_data_addr(
			vars->img_player->south,
			&(vars->textures->texture_south.bits_per_pixel),
			&(vars->textures->texture_south.line_length),
			&(vars->textures->texture_south.endian));
	if (vars->textures->texture_south.addr == NULL)
		exit(1);
	vars->textures->texture_east.addr = mlx_get_data_addr(
			vars->img_player->east,
			&(vars->textures->texture_east.bits_per_pixel),
			&(vars->textures->texture_east.line_length),
			&(vars->textures->texture_east.endian));
	if (vars->textures->texture_east.addr == NULL)
		exit(1);
	vars->textures->texture_west.addr = mlx_get_data_addr(
			vars->img_player->west,
			&(vars->textures->texture_west.bits_per_pixel),
			&(vars->textures->texture_west.line_length),
			&(vars->textures->texture_west.endian));
	if (vars->textures->texture_west.addr == NULL)
		exit(1);
}

void	get_img(t_vars *vars)
{
	vars->img_renga = mlx_xpm_file_to_image(vars->mlx, "./img/renga.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_renga == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_grass = mlx_xpm_file_to_image(vars->mlx, "./img/grass.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_grass == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->north = mlx_xpm_file_to_image(vars->mlx, "./img/north.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->north == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->south = mlx_xpm_file_to_image(vars->mlx, "./img/south.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->south == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->east = mlx_xpm_file_to_image(vars->mlx, "./img/east.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->east == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->img_player->west = mlx_xpm_file_to_image(vars->mlx, "./img/west.xpm",
			&(vars->img_width), &(vars->img_height));
	if (vars->img_player->west == NULL)
		error_message_and_free(vars, "Unexpected error: mlx", 1);
	vars->textures = (t_texture_list *)malloc(sizeof(t_texture_list) * 1);
	if (vars->textures == NULL)
		exit(1); // Error
	convert_img_to_data_addr(vars);
}
