/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:22:30 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/13 13:42:14 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	word_count(const char *s, char c)
{
	size_t	words;
	int		in;

	in = 0;
	words = 0;
	while (*s)
	{
		if (*s != c && in == 0)
		{
			in = 1;
			words++;
		}
		else if (*s == c && in == 1)
			in = 0;
		s++;
	}
	return (words);
}

static char	*get_next_word(const char *s, char c, size_t *pos)
{
	size_t	start;
	char	*word;

	while (s[*pos] && s[*pos] == c)
		(*pos)++;
	start = *pos;
	while (s[*pos] && s[*pos] != c)
		(*pos)++;
	word = ft_substr(s, start, *pos - start);
	return (word);
}

static void	free_split(char **list, size_t i)
{
	while (i > 0)
	{
		i--;
		free(list[i]);
	}
	free(list);
}

static char	**allocate_words(const char *s, char c, size_t counted)
{
	char	**list;
	size_t	j;
	size_t	current;

	list = (char **)malloc((counted + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	j = 0;
	current = 0;
	while (current < counted)
	{
		list[current] = get_next_word(s, c, &j);
		if (!list[current])
		{
			free_split(list, current);
			return (NULL);
		}
		current++;
	}
	list[current] = NULL;
	return (list);
}

char	**ft_split(const char *s, char c)
{
	size_t	counted;

	if (!s)
		return (NULL);
	counted = word_count(s, c);
	return (allocate_words(s, c, counted));
}
