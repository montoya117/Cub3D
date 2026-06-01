#include "cub_3d.h"

int	is_map_line(char *line)
{
	int	i;

	if (!line || line[0] == '\0')
		return (0);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	save_map_line(char *valid_line, t_data *data)
{
	char	*line_copy;
	t_list	*new_node;
	int		len;

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

static int	map_row_error(t_data *data, int i)
{
	free_matrix(data->map.grid, i);
	data->map.grid = NULL;
	free_map_list(data->map_list);
	data->map_list = NULL;
	return (print_error("Malloc error on line width"));
}

static int	copy_map_row(t_data *data, t_list *node, int i)
{
	char	*line;

	data->map.grid[i] = malloc((data->map.width + 1) * sizeof(char));
	if (!data->map.grid[i])
		return (map_row_error(data, i));
	line = (char *)node->content;
	fill_normalized_row(data->map.grid[i], line, data->map.width);
	return (0);
}

int	convert_list_to_array(t_data *data)
{
	int		i;
	t_list	*current_node;

	if (data->map_list == NULL || data->map.height == 0)
		return (print_error("Fichero sin mapa"));
	data->map.grid = malloc((data->map.height + 1) * sizeof(char *));
	if (!data->map.grid)
		return (print_error("Malloc error en map.grid"));
	current_node = data->map_list;
	i = 0;
	while (current_node != NULL)
	{
		if (copy_map_row(data, current_node, i) != 0)
			return (1);
		current_node = current_node->next;
		i++;
	}
	data->map.grid[i] = NULL;
	free_map_list(data->map_list);
	data->map_list = NULL;
	return (0);
}

/*
int	convert_list_to_array(t_data *data)
{
	int		i;
	char	*line;
	t_list	*current_node;

	if (data->map_list == NULL || data->map.height == 0)
		return (print_error("Fichero sin mapa"));
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

*/
