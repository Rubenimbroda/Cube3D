/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_one(t_data *data, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (0);
	return (1);
}

int	load_textures(t_data *data)
{
	if (!load_one(data, &data->tex[0], data->no_path))
		return (0);
	if (!load_one(data, &data->tex[1], data->so_path))
		return (0);
	if (!load_one(data, &data->tex[2], data->we_path))
		return (0);
	if (!load_one(data, &data->tex[3], data->ea_path))
		return (0);
	return (1);
}
