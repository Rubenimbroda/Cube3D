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

#define MM_TILE 8
#define MM_PADDING 16
#define MM_RADIUS 10

static void	draw_rect(t_img *img, int x0, int y0, int size, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
			put_pixel(img, x0 + x, y0 + y, color);
	}
}

static void	draw_player_marker(t_data *data, int px, int py)
{
	int	i;
	int	dot_x;
	int	dot_y;

	draw_rect(&data->img, px - 2, py - 2, 5, 0x00FF0000);
	i = 0;
	while (i < MM_TILE)
	{
		dot_x = px + (int)(data->player.dir_x * i);
		dot_y = py + (int)(data->player.dir_y * i);
		if (dot_x >= 0 && dot_x < WIN_W && dot_y >= 0 && dot_y < WIN_H)
			put_pixel(&data->img, dot_x, dot_y, 0x00FF0000);
		i++;
	}
}

static void	draw_minimap(t_data *data)
{
	int	cx;
	int	cy;
	int	mx;
	int	my;
	int	draw_x;
	int	draw_y;

	cy = -MM_RADIUS - 1;
	while (++cy <= MM_RADIUS)
	{
		cx = -MM_RADIUS - 1;
		while (++cx <= MM_RADIUS)
		{
			mx = (int)data->player.pos_x + cx;
			my = (int)data->player.pos_y + cy;
			draw_x = MM_PADDING + (cx + MM_RADIUS) * MM_TILE;
			draw_y = MM_PADDING + (cy + MM_RADIUS) * MM_TILE;
			if (mx < 0 || my < 0 || mx >= data->map.width || my >= data->map.height)
				draw_rect(&data->img, draw_x, draw_y, MM_TILE, 0x00202020);
			else if (data->map.grid[my][mx] == '1')
				draw_rect(&data->img, draw_x, draw_y, MM_TILE, 0x00FFFFFF);
			else
				draw_rect(&data->img, draw_x, draw_y, MM_TILE, 0x00505050);
		}
	}
	draw_player_marker(data, MM_PADDING + MM_RADIUS * MM_TILE,
		MM_PADDING + MM_RADIUS * MM_TILE);
}

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
	int		tex_h;
	double	step;
	double	tex_pos;

	y = -1;
	while (++y < ray->draw_start)
		put_pixel(&data->img, x, y, data->ceiling_color);
	ti = get_tex_index(ray);
	tex_h = data->tex[ti].height;
	step = (double)data->tex[ti].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start - 1;
	while (++y <= ray->draw_end)
	{
		if (tex_h > 0)
		{
			tex_y = (int)tex_pos % tex_h;
			if (tex_y < 0)
				tex_y += tex_h;
		}
		else
			tex_y = 0;
		tex_pos += step;
		put_pixel(&data->img, x, y,
			get_tex_color(&data->tex[ti],
				ray->tex_x * data->tex[ti].width / TEX_SIZE, tex_y));
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
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
