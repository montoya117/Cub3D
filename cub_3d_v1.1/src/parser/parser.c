#include "cub_3d.h"

// devuelve 1 si es valida 0 si no
int	check_extension(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 5)
		return (0);
	if (ft_strncmp(&str[len - 4], ".cub", 4) == 0)
		return (1);
	return (0);
}

// parser_main hace el open y un while con readline
/*
flow----->>>
parser error
free current line
drain GNL until EOF so static stash is cleaned
return 1
parser_main closes fd
main calls free_data
*/

static void	clear_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static int	read_file_lines(int fd, t_data *data)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (parser_line(line, data) != 0)
		{
			free(line);
			clear_gnl(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

// cuando haces close(fd) gnl ya ha limpiado todo !
int	parser_main(char *map_file, t_data *data)
{
	int		fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_error(strerror(errno)));
	if (read_file_lines(fd, data) != 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (data->config_count < 6)
		return (print_error("Numero de texturas o colores incorrecto"));
	if (convert_list_to_array(data) != 0)
		return (1);
	return (0);
}

// parser_line decide si es textura, color o mapa

int	parser_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
	{
		if (data->map_started == 1)
			return (print_error("Linea vacia dentro del mapa"));
		return (0);
	}
	if (is_texture_line(&line[i]))
		return (handle_texture(&line[i], data));
	if (is_color_line(&line[i]))
		return (handle_color(&line[i], data));
	if (is_map_line(line))
	{
		if (data->config_count < 6)
			return (print_error("Mapa antes de configuracion completa"));
		return (save_map_line(line, data));
	}
	return (print_error("Elemento desconocido en el archivo"));
}
