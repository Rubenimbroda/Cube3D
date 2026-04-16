/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/15 20:43:43 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	rotate_left(t_data *data)
{
	double	od;
	double	op;

	od = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-ROT_SPEED)
		- data->player.dir_y * sin(-ROT_SPEED);
	data->player.dir_y = od * sin(-ROT_SPEED)
		+ data->player.dir_y * cos(-ROT_SPEED);
	op = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-ROT_SPEED)
		- data->player.plane_y * sin(-ROT_SPEED);
	data->player.plane_y = op * sin(-ROT_SPEED)
		+ data->player.plane_y * cos(-ROT_SPEED);
}

void	rotate_right(t_data *data)
{
	double	od;
	double	op;

	od = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(ROT_SPEED)
		- data->player.dir_y * sin(ROT_SPEED);
	data->player.dir_y = od * sin(ROT_SPEED)
		+ data->player.dir_y * cos(ROT_SPEED);
	op = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(ROT_SPEED)
		- data->player.plane_y * sin(ROT_SPEED);
	data->player.plane_y = op * sin(ROT_SPEED)
		+ data->player.plane_y * cos(ROT_SPEED);
}
