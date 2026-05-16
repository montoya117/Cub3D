
#include "cub_3d.h"

int    print_error(char *str)
{
    printf("Error\n%s\n", str);
    return (1);
}

void free_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->tex_no)
		free(data->tex_no);
	if (data->tex_so)
		free(data->tex_so);
	if (data->tex_we)
		free(data->tex_we);
	if (data->tex_ea)
		free(data->tex_ea);
}