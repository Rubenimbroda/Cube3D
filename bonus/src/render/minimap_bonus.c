/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/27 00:00:00 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

#define MM_TILE     14
#define MM_PADDING  24
#define MM_RADIUS   7

#define MM_COL_BG     0x0008080F
#define MM_COL_BORDER 0x005599DD
#define MM_COL_WALL   0x00EEE0C8
#define MM_COL_FLOOR  0x00182038
#define MM_COL_VOID   0x00040408
#define MM_COL_PLAYER 0x0000FF88
#define MM_COL_DIR    0x00FFFFFF

static void	draw_player_marker(t_data *data, int px, int py)
{
	int	x;
	int	y;
	int	color;

	y = py - 5;
	while (++y <= py + 4)
	{
		x = px - 5;
		while (++x <= px + 4)
		{
			color = 0;
			if (abs(x - px) <= 2 && abs(y - py) <= 2)
				color = 0x00003322;
			else if (abs(x - px) <= 4 && abs(y - py) <= 4)
				color = MM_COL_PLAYER;
			if (color)
				put_pixel(&data->img, x, y, color);
		}
	}
	y = py + 1;
	while (--y >= py - MM_TILE * 3)
	{
		put_pixel(&data->img, px, y, MM_COL_DIR);
		put_pixel(&data->img, px + 1, y, MM_COL_DIR);
	}
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

void	draw_minimap(t_data *data)
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
