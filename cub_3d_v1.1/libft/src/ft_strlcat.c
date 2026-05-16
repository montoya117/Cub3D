/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:38:13 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/05 13:15:10 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = 0;
	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}
	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (size <= dest_len)
		return (src_len + size);
	i = 0;
	while (i < src_len && dest_len + i < size -1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/*
#include <stdio.h>
#include <stdlib.h>

int     main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./ft_strlcat \"dest\" \"src\" \"size\"\n");
        return 1;
    }
    else
    {
        unsigned int n;
        n = atoi(argv[3]);
        unsigned int result = ft_strlcat(argv[1], argv[2], n);
        printf("Result: %s\n", argv[1]);
        printf("Total length: %u\n", result);
    }
    return 0;
}
*/
