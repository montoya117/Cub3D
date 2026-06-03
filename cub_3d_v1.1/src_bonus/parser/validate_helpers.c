/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:39:44 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:39:50 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	is_open_floor(t_data *data, int row, int col)
{
	if (row == 0 || row == data->map.height - 1)
		return (1);
	if (col == 0 || col == data->map.width - 1)
		return (1);
	if (data->map.grid[row - 1][col] == ' ')
		return (1);
	if (data->map.grid[row][col - 1] == ' ')
		return (1);
	if (data->map.grid[row + 1][col] == ' ')
		return (1);
	if (data->map.grid[row][col + 1] == ' ')
		return (1);
	return (0);
}

int	flood_fill(char **tmp_grid, int col, int row, t_data *data)
{
	if (row < 0 || row >= data->map.height || col < 0 || col >= data->map.width)
		return (1);
	if (tmp_grid[row][col] == ' ' || tmp_grid[row][col] == '\0')
		return (1);
	if (tmp_grid[row][col] == '1' || tmp_grid[row][col] == 'V')
		return (0);
	tmp_grid[row][col] = 'V';
	if (flood_fill(tmp_grid, col, row - 1, data)
		|| flood_fill(tmp_grid, col + 1, row, data)
		|| flood_fill(tmp_grid, col, row + 1, data)
		|| flood_fill(tmp_grid, col - 1, row, data))
		return (1);
	return (0);
}
