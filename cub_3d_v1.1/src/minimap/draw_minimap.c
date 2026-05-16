
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
    int px;
    int py;
    int dy;

    px = (int)(data->player.pos_x * tile); //usamos data->player pos, como decimal multiplicada x tile para pasar a pixeles del minimap
    py = (int)(data->player.pos_y* tile);
    dy = -2;
    while (dy <= 2)
    {
        int dx = -2;
        while (dx <= 2)
        {
            buffer_put_pixel(&data->mlx, px + dx, py + dy, 0xFF0000); // rojo
            dx++;
        }
        dy++;
    }
}

void draw_minimap_buffer(t_data *data)
{
    int tile;
    int y;
    int x;
    char    cell;
    int color;
    tile = 10;
    y = 0;
    while (y < data->map.height)//recorremos todas las filas desde 0 hasta alto de mapa
    {
        x = 0;//inicimaos a 0 para cada columna
        while (x < data->map.width)
        {
            cell = data->map.grid[y][x];
            color = 0xCCCCCC;
            if (cell == '1')//muro
                color = 0x333333;
            else if (cell == '0')
                color = 0xAAAAAA; // suelo
            else if (cell == ' ')
                color = 0x000000; //fueraa mapa
            draw_minimap_cell(&data->mlx, tile, x, y, color);//pintamos esa celda en el buffer
            x++;
        }
        y++;
    }
    draw_player_on_minimap(data, tile);
}
