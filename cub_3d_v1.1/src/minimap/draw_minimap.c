
#include "cub_3d.h"

static void draw_minimap_cell(t_mlx *mlx, int tile, int mx, int my, int color)
{
	int py;
	int px;

	py = 0;
	while (py < tile)
	{
		px = 0;
		while (px < tile)
		{
			buffer_put_pixel(mlx, mx * tile + px, my* tile + py, color);
			/*
				x = mx * tile + px multiplicamos el tamanyo del cuadro (tile), porla posicion de x o y para saber domde empezaR
									(usamos px/y ciomo contador para pintar los pixeles justos)
				y = my * tile + py (mx y my no se mueven, solo aumentamos el contador hasta q sea uno menos que tile)
			*/
			px++;
		}
		py++;
	}

}

static void draw_player_on_minimap(t_data *data, int tile)
{
	t_minimap_player p;

	p.px = (int)(data->player.pos_x * tile);
	p.py = (int)(data->player.pos_y * tile);
	p.angle = data->player.angle;

	// Barra horizontal
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

	// Pata
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

void draw_minimap_buffer(t_data *data)
{
	t_minimap m;

	m.y = 0;
	m.max_minimap_size = 200;
	if (data->map.width > data->map.height)
		m.largest = data->map.width;
	else
		m.largest = data->map.height;
	m.tile = m.max_minimap_size / m.largest;

	while (m.y < data->map.height)
	{
		m.x = 0;
		while (m.x < data->map.width)
		{
			m.cell = data->map.grid[m.y][m.x];
			if (m.cell == '1')
				m.color = 0x333333;
			else if (m.cell == '0' || m.cell == 'N' || m.cell == 'S' || m.cell == 'E' || m.cell == 'W')
				m.color = 0xAAAAAA;
			else if (m.cell == ' ')
				m.color = 0x000000;
			else
				m.color = 0xCCCCCC;
			draw_minimap_cell(&data->mlx, m.tile, m.x, m.y, m.color);
			m.x++;
		}
		m.y++;
	}
	draw_player_on_minimap(data, m.tile);
}
