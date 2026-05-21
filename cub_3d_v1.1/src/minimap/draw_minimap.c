
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
	int	px;
	int	py;
	int	i;
	int	x;
	int	y;
	double	angle;

	px = (int)(data->player.pos_x * tile);
	py = (int)(data->player.pos_y * tile);
	angle = data->player.angle;

	// Barra horizontal
	i = -4;
	while (i <= 4)
	{
		x = px + cos(angle + M_PI_2) * i;
		y = py + sin(angle + M_PI_2) * i;
		if (x >= 0 && x < data->map.width * tile
			&& y >= 0 && y < data->map.height * tile)
			buffer_put_pixel(&data->mlx, x, y, 0xFF0000);
		i++;
	}
	// Pata
	i = 0;
	while (i <= 7)
	{
		x = px + cos(angle) * i;
		y = py + sin(angle) * i;
		if (x >= 0 && x < data->map.width * tile
			&& y >= 0 && y < data->map.height * tile)
			buffer_put_pixel(&data->mlx, x, y, 0xFF0000);
		i++;
	}
}

void draw_minimap_buffer(t_data *data)
{
    int tile;
    int y;
    int x;
    char    cell;
    int color;
    tile = fmin(WIN_W / data->map.width, WIN_H / data->map.height);
    //tile = 50; mini mapp petit
    y = 0;
    while (y < data->map.height)//recorremos todas las filas desde 0 hasta alto de mapa
    {
        x = 0;//inicimaos a 0 para cada columna
        while (x < data->map.width)
        {
            cell = data->map.grid[y][x];
            if (cell == '1')
                color = 0x333333; // pared
            else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
                color = 0xAAAAAA; // suelo o jugador encima
            else if (cell == ' ')
                 color = 0x000000; // espacio vacío
            else
                color = 0xCCCCCC; // por si acaso hay algún otro carácter
            draw_minimap_cell(&data->mlx, tile, x, y, color);//pintamos esa celda en el buffer
            x++;
        }
        y++;
    }
    draw_player_on_minimap(data, tile);
}
