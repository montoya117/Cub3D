/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:41:07 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:41:13 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	free_matrix(char **matrix, int height)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (i < height)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	**duplicate_matrix(char **src_matrix, int height)
{
	char	**dest_matrix;
	int		i;

	dest_matrix = malloc((height + 1) * sizeof(char *));
	if (!dest_matrix)
		return (NULL);
	i = 0;
	while (i < height)
	{
		dest_matrix[i] = ft_strdup(src_matrix[i]);
		if (!dest_matrix[i])
		{
			free_matrix(dest_matrix, i);
			return (NULL);
		}
		i++;
	}
	dest_matrix[i] = NULL;
	return (dest_matrix);
}
