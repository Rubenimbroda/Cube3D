/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_column(t_data *data, t_ray *ray, int x)
{
	int		y;
	int		ti;
	int		tex_y;
	double	step;
	double	tex_pos;

	y = -1;
	while (++y < ray->draw_start)
		put_pixel(&data->img, x, y, data->ceiling_color);
	ti = get_tex_index(ray);
	step = (double)data->tex[ti].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start - 1;
	while (++y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (data->tex[ti].height - 1);
		tex_pos += step;
		put_pixel(&data->img, x, y,
			get_tex_color(&data->tex[ti], ray->tex_x, tex_y));
	}
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
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
