/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/16 03:01:45 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*join_paths(char *prefix, char *path)
{
	char	*full;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(prefix);
	len2 = ft_strlen(path);
	full = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!full)
		return (NULL);
	i = -1;
	while (++i < len1)
		full[i] = prefix[i];
	while (i < len1 + len2)
	{
		full[i] = path[i - len1];
		i++;
	}
	full[i] = '\0';
	return (full);
}

static int	try_load_texture(t_data *data, t_tex *tex, char *path)
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

static int	load_one(t_data *data, t_tex *tex, char *path)
{
	char	*alt_path;

	if (try_load_texture(data, tex, path))
		return (1);
	if (!(path[0] == '.' && path[1] == '/'))
		return (0);
	alt_path = join_paths("mandatory/", path + 2);
	if (!alt_path)
		return (0);
	if (try_load_texture(data, tex, alt_path))
	{
		free(alt_path);
		return (1);
	}
	free(alt_path);
	return (0);
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
