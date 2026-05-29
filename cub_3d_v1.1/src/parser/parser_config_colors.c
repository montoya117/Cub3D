#include "cub_3d.h"

/*  
	- ** Para Colores **

	handle_color:
•	Mira si es F o C.
•	Mira si el color ya estaba puesto (si no es -1).
•	Limpia la línea y llama al siguiente paso.

	get_rgb_split:
•	Corta la línea por las comas usando ft_split.
•	IMPORTANTE: Aquí es donde se hace el free_split al final para que no haya fugas de memoria.
•	
	validate_color:
•	¿Hay 3 trozos? (Ni 2, ni 4).
•	¿Son todo números? (Sin letras).
•	¿Están entre 0 y 255?
•	rgb_to_int: El traductor.
•	Pasa los 3 números a uno solo que entienda la pantalla.
•	Fórmula: (R << 16) | (G << 8) | B.
*/

int handle_color(char *line, t_data *data)
{
	int     *target; // puntero a puntero para editar t_data->color
	char    **rgb_colors; // arrray the punteros con rgb
	char    *trimed_line;
	int     i;

	target = NULL;
	if (line[0] == 'F')
		target = &data->color_f;
	else if (line[0] == 'C')
		target = &data->color_c;
	if (!target)
		return (print_error("Identificador de color no reconocido"));
		// mirar duplicados
	if (*target != -1)
		return (print_error("Color duplicado"));
	i = 1;
	trimed_line = ft_strtrim(&line[i],  " \n\t\v\f\r");  // por si hay espacios
	if (!trimed_line)
		return (print_error("Fallo de Malloc"));
	rgb_colors = ft_split(trimed_line, ',');
	free(trimed_line); // fee antes para no hacer oble free
	if (!rgb_colors)
		return (print_error("Fallode Malloc en split"));
	if (validate_rgb(rgb_colors, target) != 0)
	{
		free_array(rgb_colors); //TODO
		return (1);
	}
	free_array(rgb_colors);
	data->config_count++; // sumaa
	return (0);
}

/*  
	asegura que el usuario no meta basura
*/

int validate_rgb(char **rgb, int *target)
{
	int r;
	int g;
	int b;

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
	1.	r << 16: Tomas el valor del Rojo (0-255) y lo mueves 16 posiciones (2 bytes) a la izquierda. Se coloca en el tercer byte.
	2.	g << 8: Tomas el Verde y lo mueves 8 posiciones (1 byte) a la izquierda. Se coloca en el segundo byte.
	3.	b: Se queda tal cual en el primer byte (posiciones 0 a 7).
	4.	| (OR): Une todos esos bits en una sola "tira" de 32 bits.
*/