/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config_colors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:39:02 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:39:06 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static int	*get_color_target(char type, t_data *data)
{
	if (type == 'F')
		return (&data->color_f);
	if (type == 'C')
		return (&data->color_c);
	return (NULL);
}

static char	**split_color_line(char *line)
{
	char	*trimed_line;
	char	**rgb_colors;

	trimed_line = ft_strtrim(&line[1], " \n\t\v\f\r");
	if (!trimed_line)
		return (NULL);
	rgb_colors = ft_split(trimed_line, ',');
	free(trimed_line);
	return (rgb_colors);
}

int	handle_color(char *line, t_data *data)
{
	int		*target;
	char	**rgb_colors;

	target = get_color_target(line[0], data);
	if (!target)
		return (print_error("Identificador de color no reconocido"));
	if (*target != -1)
		return (print_error("Color duplicado"));
	rgb_colors = split_color_line(line);
	if (!rgb_colors)
		return (print_error("Formato o memoria insuficiente en colores"));
	if (validate_rgb(rgb_colors, target) != 0)
	{
		free_array(rgb_colors);
		return (1);
	}
	free_array(rgb_colors);
	data->config_count++;
	return (0);
}

int	validate_rgb(char **rgb, int *target)
{
	int	r;
	int	g;
	int	b;

	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (print_error("El color debe tener 3 componentes (R,G,B)"));
	if (!is_str_digit(rgb[0]) || !is_str_digit(rgb[1]) || !is_str_digit(rgb[2]))
		return (print_error("Los colores deben ser solo numeros"));
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error("Colores fuera de rango (0-255)"));
	*target = (r << 16) | (g << 8) | b;
	return (0);
}

/*  
	(Bit-shifting)
	*target = (r << 16) | (g << 8) | b;
	1.	r << 16: Tomas el valor del Rojo (0-255) y lo mueves 16 posiciones 
		(2 bytes) a la izquierda. Se coloca en el tercer byte.
	2.	g << 8: Tomas el Verde y lo mueves 8 posiciones (1 byte) a la 
		izquierda. Se coloca en el segundo byte.
	3.	b: Se queda tal cual en el primer byte (posiciones 0 a 7).
	4.	| (OR): Une todos esos bits en una sola "tira" de 32 bits.
*/
