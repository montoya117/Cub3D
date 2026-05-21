#include "cub_3d.h"
// ---- FUNCION PRINCIPAL: handle_keypress ----

int handle_keypress(int keycode, t_data *data)
{
    if (keycode == 65307) // ESC
        exit(0);

    rotate_player(keycode, data);
    move_player(keycode, data);

    return (0);
}