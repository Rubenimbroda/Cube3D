/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/16 03:21:34 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit(data, "Failed to initialize mlx");
	data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "cub3D");
	if (!data->win)
		error_exit(data, "Failed to create window");
	data->img.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (!data->img.img)
		error_exit(data, "Failed to create image");
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bpp, &data->img.line_len, &data->img.endian);
}

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, X_EVENT_KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->win, X_EVENT_KEY_RELEASE, 1L << 1,
		key_release, data);
	mlx_hook(data->win, X_EVENT_MOTION, X_MASK_MOTION, mouse_move, data);
	mlx_hook(data->win, X_EVENT_DESTROY, 0, close_window, data);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(data->mlx, render_frame, data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
		return (1);
	}
	init_data(&data);
	if (!parse_file(&data, argv[1]))
		error_exit(&data, "Invalid map or scene file");
	init_mlx(&data);
	if (!load_textures(&data))
		error_exit(&data, "Failed to load textures");
	setup_hooks(&data);
	mlx_loop(data.mlx);
	free_data(&data);
	return (0);
}
