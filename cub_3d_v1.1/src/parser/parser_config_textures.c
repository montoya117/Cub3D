
#include "cub_3d.h"

/*
	- ** Para Texturas **
	- handle_texture;: Extrae y limpia la ruta de la imagen (NO, SO, etc.).

*/
int handle_texture(char *line, t_data *data)
{
	char    **target;
	int     i;

	target = NULL;
	if (ft_strncmp(line, "NO", 2) == 0)
		target = &data->tex_path_no;
	else if (ft_strncmp(line, "SO", 2) == 0)
		target = &data->tex_path_so;
	else if (ft_strncmp(line, "WE", 2) == 0)
		target = &data->tex_path_we;
	else if (ft_strncmp(line, "EA", 2) == 0)
		target = &data->tex_path_ea;
	// por si acaso
	if (!target)
		return (print_error("Identificador de textura inválido"));
	// mirar duplicados
	// segunda vuelta el path ya esta editado asi k sale
	if (*target != NULL)
		return (print_error("Textura duplicada"));
	// salto NO,SO...
	i = 2;
	*target = ft_strtrim(&line[i], " \n\t\v\f\r"); 
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


