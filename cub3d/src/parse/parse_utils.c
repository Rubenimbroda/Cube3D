/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	ft_atoi_safe(char *s, int *val)
{
	int	i;
	int	result;

	if (!s || !s[0])
		return (0);
	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		result = result * 10 + (s[i] - '0');
		if (result > 255)
			return (0);
		i++;
	}
	*val = result;
	return (1);
}

char	*ft_strtrim_ws(char *s)
{
	int		start;
	int		end;
	char	*res;
	int		i;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] && ft_isspace(s[start]))
		start++;
	end = ft_strlen(s) - 1;
	while (end > start && ft_isspace(s[end]))
		end--;
	res = malloc(sizeof(char) * (end - start + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (start <= end)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
