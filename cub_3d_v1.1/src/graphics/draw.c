
#include "cub_3d.h"
#include <math.h>
#define FOV (M_PI / 3)   // 60 grados

void    draw(t_data *data)
{
    draw_minimap_buffer(data);
    //ya anyadiremos mas cosas !! :3

        // ----------- Prueba: columna vertical -----------
    double dir_angle = data->player.dir; // dirección actual del jugador (en radianes)

    for (int x = 0; x < WIN_W; x++)
    {
        double percent = (double)x / (double)WIN_W;
        double ray_angle = dir_angle - (FOV / 2) + percent * FOV;

        // Dirección del rayo
        double dir_x = cos(ray_angle);
        double dir_y = sin(ray_angle);

        // Posición inicial del rayo (centro del jugador)
        double ray_x = data->player.pos_x + 0.5;
        double ray_y = data->player.pos_y + 0.5;

        // Lanza el rayo paso a paso hasta chocar con un muro
        double dist = 0.0, step = 0.01;
        int hit = 0;
        while (!hit && dist < 20.0)
        {
            ray_x += dir_x * step;
            ray_y += dir_y * step;
            dist += step;
            int map_x = (int)ray_x;
            int map_y = (int)ray_y;
            if (data->map.grid[map_y][map_x] == '1')
                hit = 1;
        }

        // Corrige el efecto "ojos de pez" (fisheye)
        dist = dist * cos(ray_angle - dir_angle);

        // Altura de la pared en pantalla
        int line_height = (int)(WIN_H / dist);

        // Dibuja la columna vertical en la pantalla
        int y_start = WIN_H / 2 - line_height / 2;
        int y_end = WIN_H / 2 + line_height / 2;

        unsigned int color = 0xCCCCCC; // color pared
        for (int y = y_start; y < y_end; y++)
            if (y >= 0 && y < WIN_H)
                buffer_put_pixel(&data->mlx, x, y, color);
    }
    // ------------------------------------------------
}
