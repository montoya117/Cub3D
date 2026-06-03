/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:39:35 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:39:36 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	check_elements(t_data *data)
{
	if (data->tex_path_no == NULL
		|| data->tex_path_so == NULL
		|| data->tex_path_we == NULL
		|| data->tex_path_ea == NULL)
		return (print_error("Faltan identificadores de textura esenciales"));
	if (data->color_c == -1 || data->color_f == -1)
		return (print_error("Faltan los colores de techo o suelo"));
	if (data->config_count != 6)
		return (print_error("Número de elementos de configuración incorrecto"));
	return (0);
}

int	check_all_floors_closed(t_data *data)
{
	int	row;
	int	col;

	row = 0;
	while (row < data->map.height)
	{
		col = 0;
		while (col < data->map.width)
		{
			if (data->map.grid[row][col] == '0')
			{
				if (is_open_floor(data, row, col))
					return (print_error("Espacios internos inválidos"));
			}
			col++;
		}
		row++;
	}
	return (0);
}

int	check_walls(t_data *data)
{
	char	**tmp_grid;
	int		is_open;

	tmp_grid = duplicate_matrix(data->map.grid, data->map.height);
	if (!tmp_grid)
		return (print_error("Malloc error al duplicar mapa de validación"));
	is_open = flood_fill(tmp_grid,
			(int)data->player.pos_x, (int)data->player.pos_y, data);
	free_matrix(tmp_grid, data->map.height);
	if (is_open)
		return (print_error("El mapa está abierto. No rodeado por muros"));
	return (0);
}

int	validate_elements_and_map(t_data *data)
{
	if (check_elements(data) != 0)
		return (1);
	if (check_player(data) != 0)
		return (1);
	if (check_all_floors_closed(data) != 0)
		return (1);
	if (check_walls(data) != 0)
		return (1);
	return (0);
}
