/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaime <jaime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/03/17 00:00:00 by jaime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char const *s, char c, int *idx)
{
	int		start;
	int		len;
	char	*word;

	while (s[*idx] && s[*idx] == c)
		(*idx)++;
	start = *idx;
	len = 0;
	while (s[*idx] && s[*idx] != c)
	{
		len++;
		(*idx)++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	len = -1;
	while (++len < *idx - start)
		word[len] = s[start + len];
	word[len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;
	int		i;
	int		idx;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = -1;
	idx = 0;
	while (++i < words)
	{
		result[i] = get_word(s, c, &idx);
		if (!result[i])
		{
			free_split(result);
			return (NULL);
		}
	}
	result[i] = NULL;
	return (result);
}
