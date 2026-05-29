
#include "cub_3d.h"

/*
	- is_map_line: Detecta si la línea contiene solo 01NSEW y espacios.
	- save_map_line: Guarda la línea temporalmente (en una lista o un string acumulado).
	- convert_list_to_array: Transforma lo guardado en el char **grid final.
*/

/*

1. Pseudocódigo de is_map_line
Esta función solo debe decir "sí" o "no" (1 o 0). Su único objetivo es verificar que la línea no tenga caracteres prohibidos.

*/

int is_map_line(char *line)
{
	int i;

	if (!line || line[0] == '\0')
		return (0); // not valid
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' '  && line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

/*
2. Pseudocódigo de save_map_line
*/

int save_map_line(char *valid_line, t_data *data)
{
	char    *line_copy;
	t_list  *new_node;
	int     len;
	
	data->map_started = 1;
	line_copy = ft_strdup(valid_line);
	if (!line_copy)
		return (print_error("Malloc error in map"));
	new_node = ft_lstnew(line_copy);
	if (!new_node)
	{
		free(line_copy);
		return (print_error("Malloc nodes map error"));
	}
	ft_lstadd_back(&(data->map_list), new_node);
	data->map.height++;
	len = ft_strlen(valid_line);
	if (len > data->map.width)
		data->map.width = len;
	return (0);
}

/*
3. Pseudocódigo de convert_list_to_array
Esta función se ejecuta al terminar el GNL. Transforma la lista enlazada temporal en el char **grid final.
*/
static void fill_normalized_row(char *dst, char *src, int width)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
}

int convert_list_to_array(t_data *data)
{
	int     i;
	char    *line;
	t_list  *current_node;
	
	// checks
	if (data->map_list == NULL || data->map.height == 0)
		return (print_error("Fichero sin mapa"));
	// reservo memoria para grid
	data->map.grid = malloc((data->map.height + 1) * sizeof(char *));
	if (!data->map.grid)
		return (print_error("Malloc error en map.grid"));
	current_node = data->map_list;
	i = 0;
	while (current_node != NULL)
	{
		data->map.grid[i] = malloc((data->map.width + 1) * sizeof(char));
		if (!data->map.grid[i])
		{
			free_matrix(data->map.grid, i);
			data->map.grid = NULL;
			free_map_list(data->map_list);
			data->map_list = NULL;
			return (print_error("Malloc error on line width"));
		}
		line = (char *)current_node->content;
		fill_normalized_row(data->map.grid[i], line, data->map.width);
		current_node = current_node->next;
		i++;
	}
	data->map.grid[i] = NULL;
	free_map_list(data->map_list);
	data->map_list = NULL;
	return (0);
}

/*
line = (char *)current_node->content;
fill_normalized_row(data->map.grid[i], line, data->map.width);
*/
