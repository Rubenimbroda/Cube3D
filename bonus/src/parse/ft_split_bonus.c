/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruben <ruben@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by jaime             #+#    #+#             */
/*   Updated: 2026/04/15 20:43:50 by ruben            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

static char	**alloc_result(int words)
{
	char	**result;
	int		j;

	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	j = -1;
	while (++j <= words)
		result[j] = NULL;
	return (result);
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
	result = alloc_result(words);
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
