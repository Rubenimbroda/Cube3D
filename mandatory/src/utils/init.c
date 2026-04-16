/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_keys_and_tex(t_data *data)
{
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->tex[0].img = NULL;
	data->tex[1].img = NULL;
	data->tex[2].img = NULL;
	data->tex[3].img = NULL;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img.img = NULL;
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->parse_flags = 0;
	init_keys_and_tex(data);
}
