/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/05 05:22:06 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_xpm_image(t_vars *vars, void **img, char *path)
{
	*img = mlx_xpm_file_to_image(vars->mlx, path,
			&(vars->img_width), &(vars->img_height));
	if (*img == NULL)
		error_message_and_free(vars, "Cannot load texture", 1);
}

void	load_basic_images(t_vars *vars)
{
	load_xpm_image(vars, &(vars->img_renga), "./img/renga.xpm");
	load_xpm_image(vars, &(vars->img_grass), "./img/grass.xpm");
}

void	load_player_images(t_vars *vars)
{
	load_xpm_image(vars, &(vars->img_player->north), "./img/north.xpm");
	load_xpm_image(vars, &(vars->img_player->south), "./img/south.xpm");
	load_xpm_image(vars, &(vars->img_player->east), "./img/east.xpm");
	load_xpm_image(vars, &(vars->img_player->west), "./img/west.xpm");
}
