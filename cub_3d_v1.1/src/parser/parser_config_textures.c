#include "cub_3d.h"

static char	**get_texture_target(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (&data->tex_path_no);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (&data->tex_path_so);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (&data->tex_path_we);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (&data->tex_path_ea);
	return (NULL);
}

int	handle_texture(char *line, t_data *data)
{
	char	**target;

	target = get_texture_target(line, data);
	if (!target)
		return (print_error("Identificador de textura inválido"));
	if (*target != NULL)
		return (print_error("Textura duplicada"));
	*target = ft_strtrim(&line[2], " \n\t\v\f\r");
	if (!*target)
		return (print_error("Fallo de Malloc"));
	if ((*target)[0] == '\0')
	{
		free(*target);
		*target = NULL;
		return (print_error("Ruta de textura vacia"));
	}
	data->config_count++;
	return (0);
}
