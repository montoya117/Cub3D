/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:55:28 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/12 13:22:29 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t n)
{
	unsigned char	*temp;
	size_t			i;

	temp = ((unsigned char *) dest);
	i = 0;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}
