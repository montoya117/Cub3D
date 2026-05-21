/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:05:36 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/12 13:46:01 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)src;
	c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (c == s[i])
			return ((void *)(&s[i]));
		i++;
	}
	return (NULL);
}
