/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/15 03:38:39 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_partial_map(char **grid, int filled)
{
	int	i;

	i = -1;
	while (++i < filled)
		free(grid[i]);
	free(grid);
}

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
		data->map.grid[i] = NULL;
	i = -1;
	while (++i < count)
	{
		data->map.grid[i] = pad_line(lines[start + i], width);
		if (!data->map.grid[i])
		{
			free_partial_map(data->map.grid, i);
			data->map.grid = NULL;
			data->map.width = 0;
			data->map.height = 0;
			return (0);
		}
	}
	return (1);
}
