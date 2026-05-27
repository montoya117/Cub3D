
#include "cub_3d.h"
#include <math.h>

static	void	find_ray_hit(t_data *data, double ray_angle, double *dist)
{
	t_ray	r;

	r.dir_x = cos(ray_angle);
	r.dir_y = sin(ray_angle);
	r.ray_x = data->player.pos_x;
	r.ray_y = data->player.pos_y;
	*dist = 0.0;
	r.step = 0.01;
	r.hit = 0;
	while (!r.hit && *dist < 20.0)
	{
		r.ray_x += r.dir_x * r.step;
		r.ray_y += r.dir_y * r.step;
		*dist += r.step;
		r.map_x = (int)r.ray_x;
		r.map_y = (int)r.ray_y;
		if (r.map_y < 0 || r.map_y >= data->map.height
			|| r.map_x < 0
			|| r.map_x >= (int)ft_strlen(data->map.grid[r.map_y]))
			r.hit = 1;
		else if (data->map.grid[r.map_y][r.map_x] == '1')
			r.hit = 1;
	}
}

static void	draw_column(t_data *data, int x, double dir_angle)
{
	t_col	c;

	c.percent = (double)x / (double)WIN_W;
	c.ray_angle = dir_angle - (FOV / 2) + c.percent * FOV;
	find_ray_hit(data, c.ray_angle, &c.dist);
	c.dist = c.dist * cos(c.ray_angle - dir_angle);
	if (c.dist < 0.00001)
		c.dist = 0.00001;
	c.line_height = (int)(WIN_H / c.dist);
	c.y_start = WIN_H / 2 - c.line_height / 2;
	c.y_end = WIN_H / 2 + c.line_height / 2;
	c.y = c.y_start;
	while (c.y < c.y_end)
	{
		if (c.y >= 0 && c.y < WIN_H)
			buffer_put_pixel(&data->mlx, x, c.y, 0xCCCCCC);
		c.y++;
	}
}

void	draw(t_data *data)
{
	int		x;
	double	dir_angle;

	dir_angle = data->player.angle;
	x = 0;
	while (x < WIN_W)
	{
		draw_column(data, x, dir_angle);
		x++;
	}
	draw_minimap_buffer(data);
}
