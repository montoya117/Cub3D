/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemonto <alemonto@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:16:41 by alemonto          #+#    #+#             */
/*   Updated: 2025/05/12 16:48:12 by alemonto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MY_INT_MAX 2147483647
#define MY_INT_MIN -2147483648

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		if (result > MY_INT_MAX && sign == 1)
			return (MY_INT_MAX);
		if (result > (long long)MY_INT_MAX + 1 && sign == -1)
			return (MY_INT_MIN);
		str++;
	}
	return (sign * result);
}
