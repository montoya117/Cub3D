/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:21:56 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/12 16:40:00 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*return_empty_string(void)
{
	char	*empty;

	empty = (char *)malloc(1);
	if (!empty)
		return (NULL);
	empty[0] = '\0';
	return (empty);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	int		start;
	int		end;
	int		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = (ft_strlen(s1) - 1);
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	if (end < start)
		return (return_empty_string());
	trimed = (char *)malloc(((end - start) + 2) * sizeof(char));
	if (!trimed)
		return (NULL);
	len = 0;
	while (start <= end)
		trimed[len++] = s1[start++];
	trimed[len] = '\0';
	return (trimed);
}
// Find the start
// Find the end
// Allocate memory
// Copy the substring (start to end)
// Null terminate
