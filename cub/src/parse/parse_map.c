/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(char **lines, int start, int count)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = -1;
	while (++i < count)
	{
		len = ft_strlen(lines[start + i]);
		if (len > max)
			max = len;
	}
	return (max);
}

static char	*pad_line(char *line, int width)
{
	char	*padded;
	int		len;
	int		i;

	len = ft_strlen(line);
	padded = malloc(sizeof(char) * (width + 1));
	if (!padded)
		return (NULL);
	i = -1;
	while (++i < len)
		padded[i] = line[i];
	while (i < width)
		padded[i++] = ' ';
	padded[i] = '\0';
	return (padded);
}

int	parse_map(t_data *data, char **lines, int start, int count)
{
	int	i;
	int	width;

	width = get_max_width(lines, start, count);
	data->map.width = width;
	data->map.height = count;
	data->map.grid = malloc(sizeof(char *) * count);
	if (!data->map.grid)
		return (0);
	i = -1;
	while (++i < count)
	{
		data->map.grid[i] = pad_line(lines[start + i], width);
		if (!data->map.grid[i])
			return (0);
	}
	return (1);
}
