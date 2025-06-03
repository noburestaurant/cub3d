/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/01 16:33:10 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validation_and_parse(int argc, char **argv, t_vars *vars)
{
	if (argc != 2)
		error_message_and_free(vars, "Invalid number of arguments", 1);
	check_args(argv[1]);
	vars->map = get_map(argv[1]);
	if (vars->map == NULL)
		error_message_and_free(vars, "Unexpected Error\n", 1);
	parse_map(vars);
}
