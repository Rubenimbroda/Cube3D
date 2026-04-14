/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_data *data, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || mx >= data->map.width)
		return (1);
	if (my < 0 || my >= data->map.height)
		return (1);
	return (data->map.grid[my][mx] == '1');
}

void	move_forward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	ny = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	if (!is_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (!is_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	move_backward(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	ny = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	if (!is_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (!is_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	move_left(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x - data->player.plane_x * MOVE_SPEED;
	ny = data->player.pos_y - data->player.plane_y * MOVE_SPEED;
	if (!is_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (!is_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}

void	move_right(t_data *data)
{
	double	nx;
	double	ny;

	nx = data->player.pos_x + data->player.plane_x * MOVE_SPEED;
	ny = data->player.pos_y + data->player.plane_y * MOVE_SPEED;
	if (!is_wall(data, nx, data->player.pos_y))
		data->player.pos_x = nx;
	if (!is_wall(data, data->player.pos_x, ny))
		data->player.pos_y = ny;
}
