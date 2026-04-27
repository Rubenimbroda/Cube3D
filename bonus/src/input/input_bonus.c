/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/16 03:27:11 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	if (keycode == KEY_W)
		data->keys.w = 1;
	if (keycode == KEY_S)
		data->keys.s = 1;
	if (keycode == KEY_A)
		data->keys.a = 1;
	if (keycode == KEY_D)
		data->keys.d = 1;
	if (keycode == KEY_LEFT)
		data->keys.left = 1;
	if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	if (keycode == KEY_S)
		data->keys.s = 0;
	if (keycode == KEY_A)
		data->keys.a = 0;
	if (keycode == KEY_D)
		data->keys.d = 0;
	if (keycode == KEY_LEFT)
		data->keys.left = 0;
	if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	return (0);
}

void	handle_movement(t_data *data)
{
	if (data->keys.w)
		move_forward(data);
	if (data->keys.s)
		move_backward(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.left)
		rotate_left(data);
	if (data->keys.right)
		rotate_right(data);
}

static void	rotate_camera(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(angle)
		- data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x * sin(angle)
		+ data->player.dir_y * cos(angle);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle)
		+ data->player.plane_y * cos(angle);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		center_x;
	int		center_y;
	double	angle;

	(void)y;
	center_x = WIN_W / 2;
	center_y = WIN_H / 2;
	if (x == center_x)
		return (0);
	angle = (x - center_x) * MOUSE_SENSITIVITY;
	rotate_camera(data, angle);
	mlx_mouse_move(data->mlx, data->win, center_x, center_y);
	return (0);
}
