#include "cub_3d.h"

int	handle_keypress(int keycode, t_data *data)
{
    if (keycode == KEY_W)
        data->key_w = 1;
    if (keycode == KEY_A)
        data->key_a = 1;
    if (keycode == KEY_S)
        data->key_s = 1;
    if (keycode == KEY_D)
        data->key_d = 1;
    if (keycode == KEY_LEFT)
        data->key_left = 1;
    if (keycode == KEY_RIGHT)
        data->key_right = 1;
    if (keycode == KEY_ESC) // ESC (cierra juego)
        exit(0);
    return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
    if (keycode == KEY_W)
        data->key_w = 0;
    if (keycode == KEY_A)
        data->key_a = 0;
    if (keycode == KEY_S)
        data->key_s = 0;
    if (keycode == KEY_D)
        data->key_d = 0;
    if (keycode == KEY_LEFT)
        data->key_left = 0;
    if (keycode == KEY_RIGHT)
        data->key_right = 0;
    return (0);
}