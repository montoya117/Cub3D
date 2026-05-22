#include "cub_3d.h"
// ---- FUNCION PRINCIPAL: handle_keypress ----

int	handle_keypress(int keycode, t_data *data)
{
    if (keycode == 119) // W
        data->key_w = 1;
    if (keycode == 97) // A
        data->key_a = 1;
    if (keycode == 115) // S
        data->key_s = 1;
    if (keycode == 100) // D
        data->key_d = 1;
    if (keycode == 65361) // Flecha izquierda
        data->key_left = 1;
    if (keycode == 65363) // Flecha derecha
        data->key_right = 1;
    if (keycode == 65307) // ESC (cierra juego)
        exit(0);
    return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
    if (keycode == 119)
        data->key_w = 0;
    if (keycode == 97)
        data->key_a = 0;
    if (keycode == 115)
        data->key_s = 0;
    if (keycode == 100)
        data->key_d = 0;
    if (keycode == 65361)
        data->key_left = 0;
    if (keycode == 65363)
        data->key_right = 0;
    return (0);
}