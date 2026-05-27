
#include "cub_3d.h"

void	load_sprite_textures(t_data *data)
{
	int	w;
	int	h;

	data->sprite_textures[0] = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			"./sprites/explosion00.xpm", &w, &h);
	data->sprite_w = w;// GUARDA el tamaño aquí
	data->sprite_h = h;
	data->sprite_textures[1] = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			"./sprites/explosion01.xpm", &w, &h);
	data->sprite_textures[2] = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			"./sprites/explosion02.xpm", &w, &h);
}

int	init_graphics(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();//iniciamos minilibx
	if (!data->mlx.mlx_ptr)
		return (0);
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr,
			WIN_W, WIN_H, "Cub_3D");//CREAMOS VENTANA 
	if (!data->mlx.win_ptr)
		return (0);
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr,
			WIN_W, WIN_H);
	if (!data->mlx.img_ptr)
		return (0);
	data->mlx.img_data = mlx_get_data_addr(data->mlx.img_ptr,
			&data->mlx.bpp, &data->mlx.size_line, &data->mlx.endian);
	if (!data->mlx.img_data)
		return (0);
	load_sprite_textures(data);
	return (1);
}
