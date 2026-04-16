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

#define MM_TILE     14
#define MM_PADDING  24
#define MM_RADIUS   7
#define MM_BG_PAD   8

#define MM_COL_BG     0x0008080F
#define MM_COL_BORDER 0x005599DD
#define MM_COL_WALL   0x00EEE0C8
#define MM_COL_FLOOR  0x00182038
#define MM_COL_VOID   0x00040408
#define MM_COL_PLAYER 0x0000FF88
#define MM_COL_DIR    0x00FFFFFF

static void	draw_rect(t_img *img, int x0, int y0, int w, int h, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			put_pixel(img, x0 + x, y0 + y, color);
	}
}

static void	draw_dir_line(t_img *img, int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		put_pixel(img, x0, y0, MM_COL_DIR);
		put_pixel(img, x0 + 1, y0, MM_COL_DIR);
		put_pixel(img, x0, y0 + 1, MM_COL_DIR);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void	draw_player_marker(t_data *data, int px, int py)
{
	draw_rect(&data->img, px - 4, py - 4, 9, 9, MM_COL_PLAYER);
	draw_rect(&data->img, px - 2, py - 2, 5, 5, 0x00003322);
	draw_dir_line(&data->img, px, py, px, py - MM_TILE * 3);
}

static int	sample_map(t_data *data, int ox, int oy)
{
	double	wx;
	double	wy;
	int		mx;
	int		my;
	double	t;

	t = 1.0 / MM_TILE;
	wx = data->player.pos_x + ox * t * (-data->player.dir_y)
		+ oy * t * (-data->player.dir_x);
	wy = data->player.pos_y + ox * t * (data->player.dir_x)
		+ oy * t * (-data->player.dir_y);
	mx = (int)floor(wx);
	my = (int)floor(wy);
	if (mx < 0 || my < 0 || mx >= data->map.width || my >= data->map.height)
		return (MM_COL_VOID);
	if (data->map.grid[my][mx] == '1')
		return (MM_COL_WALL);
	return (MM_COL_FLOOR);
}

static void	draw_mm_border(t_img *img, int cx, int cy, int rad)
{
	int	ox;
	int	oy;
	int	d;

	oy = -rad - 7;
	while (++oy <= rad + 7)
	{
		ox = -rad - 7;
		while (++ox <= rad + 7)
		{
			d = ox * ox + oy * oy;
			if (d <= (rad + 7) * (rad + 7) && d > (rad + 4) * (rad + 4))
				put_pixel(img, cx + ox, cy + oy, 0x00001122);
			else if (d <= (rad + 4) * (rad + 4) && d > (rad + 1) * (rad + 1))
				put_pixel(img, cx + ox, cy + oy, MM_COL_BORDER);
			else if (d <= (rad + 1) * (rad + 1) && d > rad * rad)
				put_pixel(img, cx + ox, cy + oy, MM_COL_BG);
		}
	}
}

static void	draw_minimap(t_data *data)
{
	int	rad;
	int	pcx;
	int	pcy;
	int	ox;
	int	oy;

	rad = (2 * MM_RADIUS + 1) * MM_TILE / 2;
	pcx = MM_PADDING + rad;
	pcy = MM_PADDING + rad;
	draw_mm_border(&data->img, pcx, pcy, rad);
	oy = -rad - 1;
	while (++oy <= rad)
	{
		ox = -rad - 1;
		while (++ox <= rad)
		{
			if (ox * ox + oy * oy > rad * rad)
				continue ;
			put_pixel(&data->img, pcx + ox, pcy + oy, sample_map(data, ox, oy));
		}
	}
	draw_player_marker(data, pcx, pcy);
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
