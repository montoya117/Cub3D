/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:02:53 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/12 14:27:11 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	tofind_len;

	i = 0;
	if (*tofind == '\0')
		return ((char *)str);
	tofind_len = ft_strlen(tofind);
	while (str[i] && i + tofind_len <= n)
	{
		j = 0;
		while (i + j < n && str[i + j] && tofind[j] && str[i + j] == tofind[j])
		{
			j++;
		}
		if (tofind[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
/*
// ptr = str[i] IS WRONG
// ptr = &str[i]; because &str[i] poitn to the address
*/
