/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/15 03:38:39 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_rgb_component(char *raw, int *out)
{
	char	*trim;
	int		ok;

	trim = ft_strtrim_ws(raw);
	if (!trim)
		return (0);
	ok = ft_atoi_safe(trim, out);
	free(trim);
	return (ok);
}

static int	set_floor(t_data *data, char **p)
{
	int	r;
	int	g;
	int	b;

	if (!parse_rgb_component(p[0], &r) || !parse_rgb_component(p[1], &g)
		|| !parse_rgb_component(p[2], &b))
		return (-1);
	data->floor_color = create_rgb(r, g, b);
	return (1);
}

static int	set_ceiling(t_data *data, char **p)
{
	int	r;
	int	g;
	int	b;

	if (!parse_rgb_component(p[0], &r) || !parse_rgb_component(p[1], &g)
		|| !parse_rgb_component(p[2], &b))
		return (-1);
	data->ceiling_color = create_rgb(r, g, b);
	return (1);
}

static int	check_dup_color(t_data *data, int is_floor)
{
	int	bit;

	bit = 4 + !is_floor;
	if (data->parse_flags & (1 << bit))
		return (0);
	data->parse_flags |= (1 << bit);
	return (1);
}

int	parse_color(t_data *data, char *line, int is_floor)
{
	char	*trimmed;
	char	**parts;
	int		count;
	int		ret;

	if (!check_dup_color(data, is_floor))
		return (-1);
	trimmed = ft_strtrim_ws(line + 1);
	if (!trimmed)
		return (-1);
	parts = ft_split(trimmed, ',');
	free(trimmed);
	if (!parts)
		return (-1);
	count = 0;
	while (parts[count])
		count++;
	ret = -1;
	if (count == 3 && is_floor)
		ret = set_floor(data, parts);
	else if (count == 3)
		ret = set_ceiling(data, parts);
	free_split(parts);
	return (ret);
}
