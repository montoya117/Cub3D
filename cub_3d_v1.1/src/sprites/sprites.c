
#include "cub_3d.h"

void	draw_explosion_in_buffer(t_data *data)
{
	t_explosion_helper	v;

	if (!data->explosion.active
		|| data->explosion.frame < 0
		|| data->explosion.frame >= SPRITE_FRAMES)
		return ;
	v.img = data->sprite_textures[data->explosion.frame];
	v.sprite_data = mlx_get_data_addr(v.img, &v.bpp, &v.size_line, &v.endian);
	v.w = data->sprite_w;
	v.h = data->sprite_h;
	v.ox = 320;
	v.oy = 240;
	v.y = -1;
	while (++v.y < v.h)
	{
		v.x = -1;
		while (++v.x < v.w)
		{
			v.pixel_offset = v.y * v.size_line + v.x * (v.bpp / 8);
			v.color = *(unsigned int *)(v.sprite_data + v.pixel_offset);
			if ((v.color & 0x00FFFFFF) != 0x000000)
				buffer_put_pixel(&data->mlx, v.ox + v.x, v.oy + v.y, v.color);
		}
	}
}

void	update_explosion_anim(t_data *data)
{
	if (!data->explosion.active)
		return ;
	data->explosion.tick++;
	if (data->explosion.tick > data->explosion.delay)
	{
		data->explosion.tick = 0;
		data->explosion.frame++;
		if (data->explosion.frame >= SPRITE_FRAMES)
		{
			data->explosion.active = 0;// termina la animmacion
			data->explosion.frame = 0;// vuelveemos al frame 0 por seguridad
		}
	}
}
