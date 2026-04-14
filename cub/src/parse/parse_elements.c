/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*extract_path(char *line)
{
	int		i;

	i = 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (NULL);
	return (ft_strtrim_ws(&line[i]));
}

static int	set_tex_path(t_data *data, char *line, int idx)
{
	char	*path;

	if (data->parse_flags & (1 << idx))
		return (-1);
	data->parse_flags |= (1 << idx);
	path = extract_path(line);
	if (!path)
		return (-1);
	if (idx == 0)
		data->no_path = path;
	else if (idx == 1)
		data->so_path = path;
	else if (idx == 2)
		data->we_path = path;
	else
		data->ea_path = path;
	return (1);
}

static int	check_tex_id(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		return (0);
	if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		return (1);
	if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		return (2);
	if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		return (3);
	return (-1);
}

static int	dispatch_element(t_data *data, char *tr)
{
	int	idx;

	idx = check_tex_id(tr);
	if (idx >= 0)
		return (set_tex_path(data, tr, idx));
	if (tr[0] == 'F' && ft_isspace(tr[1]))
		return (parse_color(data, tr, 1));
	if (tr[0] == 'C' && ft_isspace(tr[1]))
		return (parse_color(data, tr, 0));
	if (is_map_char(tr[0]))
		return (2);
	return (-1);
}

int	parse_element(t_data *data, char *line)
{
	int		ret;
	char	*tr;

	tr = ft_strtrim_ws(line);
	if (!tr)
		return (-1);
	if (tr[0] == '\0')
	{
		free(tr);
		return (0);
	}
	ret = dispatch_element(data, tr);
	free(tr);
	return (ret);
}
