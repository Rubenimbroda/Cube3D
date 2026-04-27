/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/16 03:27:12 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"

# define WIN_W 1280
# define WIN_H 720
# define TEX_SIZE 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MOUSE_SENSITIVITY 0.002

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_MOTION 6
# define X_EVENT_DESTROY 17
# define X_MASK_MOTION 64L

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
}	t_ray;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_lines
{
	char	**arr;
	int		count;
	int		cap;
}	t_lines;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_tex		tex[4];
	t_player	player;
	t_map		map;
	t_keys		keys;
	int			floor_color;
	int			ceiling_color;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			parse_flags;
}	t_data;

/* parse */
int		parse_file(t_data *data, char *file);
int		parse_element(t_data *data, char *line);
int		parse_color(t_data *data, char *line, int is_floor);
int		parse_map(t_data *data, char **lines, int start, int count);
int		validate_map(t_data *data);
int		check_cell_valid(t_data *data, int y, int x);
int		set_player_ns(t_data *data, int y, int x, int *count);
int		set_player_ew(t_data *data, int y, int x, int *count);

/* parse utils */
char	*ft_strtrim_ws(char *s);
int		ft_isspace(char c);
char	*get_next_line(int fd);
int		ft_atoi_safe(char *s, int *val);
int		is_map_char(char c);
char	**ft_split(char const *s, char c);
int		store_line(t_lines *lines, char *line);
void	free_lines(t_lines *lines);
int		check_no_empty_in_map(char **lines, int start, int total);

/* render */
int		render_frame(t_data *data);
void	draw_minimap(t_data *data);
void	cast_ray(t_data *data, t_ray *ray, int x);
void	init_ray(t_data *data, t_ray *ray, int x);
void	perform_dda(t_data *data, t_ray *ray);
void	calc_wall(t_data *data, t_ray *ray);
void	draw_column(t_data *data, t_ray *ray, int x);
int		get_tex_color(t_tex *tex, int x, int y);

/* textures */
int		load_textures(t_data *data);

/* input */
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	handle_movement(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		is_wall(t_data *data, double x, double y);

/* utils */
void	put_pixel(t_img *img, int x, int y, int color);
int		create_rgb(int r, int g, int b);
int		close_window(t_data *data);
void	free_data(t_data *data);
void	free_split(char **split);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
void	error_exit(t_data *data, char *msg);
void	init_data(t_data *data);

#endif
