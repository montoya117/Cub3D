/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:37:50 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:37:55 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static void	put_cell_pixel(t_mlx *mlx, t_cell cell)
{
	int	py;
	int	px;

	py = 0;
	while (py < cell.tile)
	{
		px = 0;
		while (px < cell.tile)
		{
			buffer_put_pixel(mlx, cell.x * cell.tile + px,
				cell.y * cell.tile + py, cell.color);
			px++;
		}
		py++;
	}
}

static int	get_cell_color(char cell)
{
	if (cell == '1')
		return (0x333333);
	else if (cell == '0' || cell == 'N'
		|| cell == 'S' || cell == 'E' || cell == 'W')
		return (0xAAAAAA);
	else if (cell == ' ')
		return (0x000000);
	return (0xCCCCCC);
}

static void	draw_minimap_cells(t_data *data, int tile)
{
	int		x;
	int		y;
	char	cellchar;
	t_cell	cell;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			cell.x = x;
			cell.y = y;
			cell.tile = tile;
			cellchar = data->map.grid[y][x];
			cell.color = get_cell_color(cellchar);
			put_cell_pixel(&data->mlx, cell);
			x++;
		}
		y++;
	}
}

static void	draw_player_minimap(t_data *data, int tile)
{
	t_minimap_player	p;

	p.px = (int)(data->player.pos_x * tile);
	p.py = (int)(data->player.pos_y * tile);
	p.angle = data->player.angle;
	p.i = -4;
	while (p.i <= 4)
	{
		p.x = p.px + cos(p.angle + M_PI_2) * p.i;
		p.y = p.py + sin(p.angle + M_PI_2) * p.i;
		if (p.x >= 0 && p.x < data->map.width * tile
			&& p.y >= 0 && p.y < data->map.height * tile)
			buffer_put_pixel(&data->mlx, p.x, p.y, 0xFF0000);
		p.i++;
	}
	p.i = 0;
	while (p.i <= 7)
	{
		p.x = p.px + cos(p.angle) * p.i;
		p.y = p.py + sin(p.angle) * p.i;
		if (p.x >= 0 && p.x < data->map.width * tile
			&& p.y >= 0 && p.y < data->map.height * tile)
			buffer_put_pixel(&data->mlx, p.x, p.y, 0xFF0000);
		p.i++;
	}
}

void	draw_minimap_buffer(t_data *data)
{
	int	tile;
	int	max_minimap_size;
	int	largest;

	max_minimap_size = 200;
	if (data->map.width > data->map.height)
		largest = data->map.width;
	else
		largest = data->map.height;
	tile = max_minimap_size / largest;
	draw_minimap_cells(data, tile);
	draw_player_minimap(data, tile);
}
