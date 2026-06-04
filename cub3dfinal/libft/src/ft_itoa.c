/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:58:27 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/12 18:06:31 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_digits(long n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		digits = 1;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

static char	*print_numbers(char *str, int digits, long nbl, int sign)
{
	str[digits + sign] = '\0';
	while (digits > 0)
	{
		str[digits - 1 + sign] = nbl % 10 + '0';
		nbl = nbl / 10;
		digits--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbl;
	int		digits;
	int		sign;

	nbl = n;
	digits = 0;
	sign = 0;
	if (nbl < 0)
	{
		nbl = -nbl;
		sign = 1;
	}
	digits = count_digits(nbl);
	str = (char *)malloc((digits + sign + 1) * sizeof(char));
	if (!str)
		return (NULL);
	print_numbers(str, digits, nbl, sign);
	return (str);
}
