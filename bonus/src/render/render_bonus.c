/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/16 03:21:38 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	get_tex_color(t_tex *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static int	get_tex_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (3);
		return (2);
	}
	if (ray->dir_y > 0)
		return (1);
	return (0);
}

static void	draw_wall_strip(t_data *data, t_ray *ray, int x)
{
	int		ti;
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;

	ti = get_tex_index(ray);
	step = (double)data->tex[ti].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start - 1;
	while (++y <= ray->draw_end)
	{
		if (data->tex[ti].height > 0)
		{
			tex_y = (int)tex_pos % data->tex[ti].height;
			if (tex_y < 0)
				tex_y += data->tex[ti].height;
		}
		else
			tex_y = 0;
		tex_pos += step;
		put_pixel(&data->img, x, y,
			get_tex_color(&data->tex[ti],
				ray->tex_x * data->tex[ti].width / TEX_SIZE, tex_y));
	}
}

void	draw_column(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = -1;
	while (++y < ray->draw_start)
		put_pixel(&data->img, x, y, data->ceiling_color);
	draw_wall_strip(data, ray, x);
	y = ray->draw_end;
	while (++y < WIN_H)
		put_pixel(&data->img, x, y, data->floor_color);
}

int	render_frame(t_data *data)
{
	t_ray	ray;
	int		x;

	handle_movement(data);
	x = -1;
	while (++x < WIN_W)
		cast_ray(data, &ray, x);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
