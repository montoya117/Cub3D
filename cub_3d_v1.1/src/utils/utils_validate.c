
#include "cub_3d.h"

/*
	Utilidades de matrices (Gestión del Heap)

*/
void    free_matrix(char **matrix, int  height)
{
	int i;

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

/*
FUNCIÓN duplicate_matrix(src_matrix, height):
*/

char	**duplicate_matrix(char **src_matrix, int height)
{
	char    **dest_matrix;
	int     i;

	dest_matrix = malloc((height + 1 ) * sizeof(char *));
	if (!dest_matrix)
		return (NULL);
	i = 0;
	while (i < height)
	{
		dest_matrix[i] = ft_strdup(src_matrix[i]);
		if (!dest_matrix[i])
		{
			free_matrix(dest_matrix, i);
			return(NULL);
		}
		i++;
	}
	dest_matrix[i] = NULL;
	return (dest_matrix);
}