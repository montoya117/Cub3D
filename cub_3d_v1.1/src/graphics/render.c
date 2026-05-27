
#include "cub_3d.h"

void	draw_explosion_in_buffer(t_data *data)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		w;
	int		h;
	int		ox;
	int		oy;
	int		x;
	int		y;
	int		pixel_offset;
	int		color;
	void	*img;
	char	*sprite_data;

	if (!data->explosion.active
		|| data->explosion.frame < 0
		|| data->explosion.frame >= SPRITE_FRAMES)
		return ;
	img = data->sprite_textures[data->explosion.frame];
	sprite_data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	w = data->sprite_w;
	h = data->sprite_h;
	ox = 320;
	oy = 240;
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			pixel_offset = y * size_line + x * (bpp / 8);
			color = *(unsigned int *)(sprite_data + pixel_offset);
			buffer_put_pixel(&data->mlx, ox + x, oy + y, color);
		}
	}
}

void update_explosion_anim(t_data *data)
{
    if (!data->explosion.active)
        return;
    data->explosion.tick++;
    if (data->explosion.tick > data->explosion.delay)
    {
        data->explosion.tick = 0;
        data->explosion.frame++;
        if (data->explosion.frame >= SPRITE_FRAMES)
        {
            data->explosion.active = 0; // termina la animación
            data->explosion.frame = 0;  // vuelve al frame 0 por seguridad
        }
    }
}

int render(t_data *data)
{
    process_movement(data);
    update_explosion_anim(data); // <- IMPORTANTE: llama SIEMPRE
    clear_img_buffer(&data->mlx);
    draw(data);
    draw_explosion_in_buffer(data);
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
    return (0);
}

