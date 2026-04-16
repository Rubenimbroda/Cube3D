/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_cell_valid(t_data *data, int y, int x)
{
	char	c;

	c = data->map.grid[y][x];
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	if (y == 0 || y == data->map.height - 1)
		return (0);
	if (x == 0 || x == data->map.width - 1)
		return (0);
	if (data->map.grid[y - 1][x] == ' ')
		return (0);
	if (data->map.grid[y + 1][x] == ' ')
		return (0);
	if (data->map.grid[y][x - 1] == ' ')
		return (0);
	if (data->map.grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	set_player_ns(t_data *data, int y, int x, int *count)
{
	char	c;

	c = data->map.grid[y][x];
	data->player.pos_x = x + 0.5;
	data->player.pos_y = y + 0.5;
	if (c == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	(*count)++;
	return (1);
}

int	set_player_ew(t_data *data, int y, int x, int *count)
{
	char	c;

	c = data->map.grid[y][x];
	data->player.pos_x = x + 0.5;
	data->player.pos_y = y + 0.5;
	if (c == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
	(*count)++;
	return (1);
}

static int	scan_map(t_data *data)
{
	int		y;
	int		x;
	int		pc;
	char	c;

	pc = 0;
	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			c = data->map.grid[y][x];
			if (!is_map_char(c) || !check_cell_valid(data, y, x))
				return (0);
			if (c == 'N' || c == 'S')
				set_player_ns(data, y, x, &pc);
			else if (c == 'E' || c == 'W')
				set_player_ew(data, y, x, &pc);
		}
	}
	return (pc == 1);
}

int	validate_map(t_data *data)
{
	if (!data->map.grid || data->map.height < 3 || data->map.width < 3)
		return (0);
	return (scan_map(data));
}
