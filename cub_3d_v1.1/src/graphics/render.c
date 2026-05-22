
#include "cub_3d.h"

int render(t_data *data)
{
    process_movement(data);
    clear_img_buffer(&data->mlx);
    draw(data);
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
    return (0);
}