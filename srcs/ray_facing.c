/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_facing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:03:51 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/18 11:04:24 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_ray_facing_up(float ray_angle)
{
	return (sin(ray_angle) > 0);
}

int	is_ray_facing_down(float ray_angle)
{
	return (sin(ray_angle) < 0);
}

int	is_ray_facing_right(float ray_angle)
{
	return (cos(ray_angle) > 0);
}

int	is_ray_facing_left(float ray_angle)
{
	return (cos(ray_angle) < 0);
}
