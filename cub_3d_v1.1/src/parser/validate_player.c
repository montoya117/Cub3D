/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:39:57 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:39:58 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static int	is_valid_map_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	return (0);
}

static int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

static int	set_player(t_data *data, int x, int y, char c)
{
	if (data->player.dir != '\0')
		return (print_error("El mapa contiene multiples jugadores"));
	data->player.pos_x = (double)x + 0.5;
	data->player.pos_y = (double)y + 0.5;
	data->player.dir = c;
	data->map.grid[y][x] = '0';
	return (0);
}

static int	check_player_cell(t_data *data, int x, int y)
{
	char	c;

	c = data->map.grid[y][x];
	if (!is_valid_map_char(c))
		return (print_error("El mapa contiene caracteres no permitidos"));
	if (is_player_char(c))
		return (set_player(data, x, y, c));
	return (0);
}

int	check_player(t_data *data)
{
	int	y;
	int	x;

	if (!data->map.grid)
		return (print_error("No se puede validar jugador mapa vacio"));
	y = 0;
	while (data->map.grid[y] != NULL)
	{
		x = 0;
		while (data->map.grid[y][x] != '\0')
		{
			if (check_player_cell(data, x, y) != 0)
				return (1);
			x++;
		}
		y++;
	}
	if (data->player.dir == '\0')
		return (print_error("No se encontro jugador"));
	return (0);
}

/*
int	check_player(t_data *data)
{
	int		y;
	int		x;
	char	c;

	if (!data->map.grid)
		return (print_error("No se puede validar el jugador mapa vacio"));
	y = 0;
	x = 0;
	while (data->map.grid[y] != NULL)
	{
		x = 0;
		while (data->map.grid[y][x] != '\0')
		{
			c = data->map.grid[y][x];
			if (c != 'N' && c != 'S' && c != 'W' 
            && c != 'E' && c != '0' && c != '1' && c != ' ')
				return (print_error("El mapa contiene 
                    caracteres no permitidos"));
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				if (data->player.dir != '\0')
					return (print_error("El mapa contiene múltiples jugadores"));
				data->player.pos_x = (double)x + 0.5;
				data->player.pos_y = (double)y + 0.5;
				data->player.dir = c;
				data->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (data->player.dir == '\0')
		return (print_error("No se ha encontrado la posición del jugador"));
	return (0);
}
*/
