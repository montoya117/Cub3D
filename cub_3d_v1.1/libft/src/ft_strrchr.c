/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:21:33 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/12 14:29:07 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	ch;

	last = NULL;
	ch = (char)c;
	while (*s != '\0')
	{
		if (*s == ch)
		{
			last = (char *)s;
		}
		s++;
	}
	if (ch == '\0')
	{
		return ((char *)s);
	}
	return ((char *)last);
}
/*
if (s == NULL)
		return (NULL);
*/
