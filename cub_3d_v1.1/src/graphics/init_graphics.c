
#include "cub_3d.h"

int init_graphics(t_data *data)
{
    data->mlx.mlx_ptr = mlx_init();//iniciamos minilibx
    if (!data->mlx.mlx_ptr)
        return (0);
    data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, WIN_W, WIN_H, "Cub_3D");//CREAMOS VENTANA 
    if (!data->mlx.win_ptr)
        return (0);
    data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIN_W, WIN_H);
    if (!data->mlx.img_ptr)
        return (0);
    data->mlx.img_data = mlx_get_data_addr(data->mlx.img_ptr, &data->mlx.bpp, &data->mlx.size_line, &data->mlx.endian);
    if (!data->mlx.img_data)
        return (0);
    //ANYADIR RENDER
    return(1);
}
