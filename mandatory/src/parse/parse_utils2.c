/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*ft_gnl_join(char *buf, char c)
{
	char	*new;
	int		len;

	len = ft_strlen(buf);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	if (buf)
	{
		len = 0;
		while (buf[len])
		{
			new[len] = buf[len];
			len++;
		}
		free(buf);
	}
	new[len] = c;
	new[len + 1] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	c;
	int		ret;

	line = NULL;
	ret = read(fd, &c, 1);
	while (ret > 0)
	{
		if (c == '\n')
		{
			if (!line)
				return (ft_strdup(""));
			return (line);
		}
		line = ft_gnl_join(line, c);
		if (!line)
			return (NULL);
		ret = read(fd, &c, 1);
	}
	return (line);
}

int	store_line(t_lines *lines, char *line)
{
	char	**new;
	int		i;

	if (lines->count >= lines->cap)
	{
		lines->cap = lines->cap * 2 + 16;
		new = malloc(sizeof(char *) * lines->cap);
		if (!new)
			return (0);
		i = -1;
		while (++i < lines->count)
			new[i] = lines->arr[i];
		free(lines->arr);
		lines->arr = new;
	}
	lines->arr[lines->count] = line;
	lines->count++;
	return (1);
}

void	free_lines(t_lines *lines)
{
	int	i;

	i = -1;
	while (++i < lines->count)
		free(lines->arr[i]);
	free(lines->arr);
}

int	check_no_empty_in_map(char **lines, int start, int total)
{
	int		i;
	char	*tr;
	int		found_empty;

	found_empty = 0;
	i = start - 1;
	while (++i < total)
	{
		tr = ft_strtrim_ws(lines[i]);
		if (!tr)
			return (0);
		if (tr[0] == '\0')
			found_empty = 1;
		else if (found_empty)
		{
			free(tr);
			return (0);
		}
		free(tr);
	}
	return (1);
}
