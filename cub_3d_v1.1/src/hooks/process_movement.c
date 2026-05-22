
#include "cub_3d.h"

void process_movement(t_data *data)
{
    if (data->key_w)
        move_player(119, data);
    if (data->key_a)
        move_player(97, data);
    if (data->key_s)
        move_player(115, data);
    if (data->key_d)
        move_player(100, data);
    if (data->key_left)
        rotate_player(65361, data);
    if (data->key_right)
        rotate_player(65363, data);
}