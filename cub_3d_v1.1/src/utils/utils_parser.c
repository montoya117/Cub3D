#include "cub_3d.h"

// For parser_config_colors
int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i] == ' ' || (str[i] > 9 && str[i] < 13))
		i++;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > 9)
			return (0);
		i++;
	}
	return (1);
}

// For parser_config_textures
int	is_texture_line(char *line)
{
	if ((ft_strncmp(line, "NO", 2) == 0
			|| ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0
			|| ft_strncmp(line, "EA", 2) == 0)
		&& (line[2] == ' ' || line[2] == '\t'))
		return (1);
	return (0);
}

int	is_color_line(char *line)
{
	if ((line[0] == 'F' || line[0] == 'C')
		&& (line[1] == ' ' || line[1] == '\t'))
		return (1);
	return (0);
}

// for parser_map
void	fill_normalized_row(char *dst, char *src, int width)
{
	int	i;

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
