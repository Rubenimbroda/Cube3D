/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		return (0);
	return (ft_strncmp(file + len - 4, ".cub", 4) == 0);
}

static int	find_map_start(t_data *data, t_lines *ln)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < ln->count)
	{
		ret = parse_element(data, ln->arr[i]);
		if (ret == -1)
			return (-1);
		if (ret == 2)
		{
			if ((data->parse_flags & 0x3F) != 0x3F)
				return (-1);
			return (i);
		}
	}
	return (-1);
}

static int	read_all_lines(int fd, t_lines *ln)
{
	char	*line;

	ln->arr = NULL;
	ln->count = 0;
	ln->cap = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!store_line(ln, line))
		{
			free(line);
			return (0);
		}
		line = get_next_line(fd);
	}
	return (ln->count > 0);
}

static int	process_file(t_data *data, t_lines *ln)
{
	int	map_start;
	int	map_count;

	map_start = find_map_start(data, ln);
	if (map_start < 0)
		return (0);
	if (!check_no_empty_in_map(ln->arr, map_start, ln->count))
		return (0);
	map_count = ln->count - map_start;
	if (!parse_map(data, ln->arr, map_start, map_count))
		return (0);
	return (validate_map(data));
}

int	parse_file(t_data *data, char *file)
{
	int		fd;
	t_lines	ln;
	int		ok;

	if (!check_extension(file))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!read_all_lines(fd, &ln))
	{
		close(fd);
		return (0);
	}
	close(fd);
	ok = process_file(data, &ln);
	free_lines(&ln);
	return (ok);
}
