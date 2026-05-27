
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


/*
 referencia logica

 static void find_ray_hit(t_data *data, double ray_angle,
        double *dist, int *side, double *wall_x)
{
    t_ray  r;
    double diff_x;
    double diff_y;

    r.dir_x = cos(ray_angle);
    r.dir_y = sin(ray_angle);
    r.ray_x = data->player.pos_x;
    r.ray_y = data->player.pos_y;
    *dist = 0.0;
    r.step = 0.005;
    r.hit = 0;
    while (!r.hit && *dist < 20.0)
    {
        r.ray_x += r.dir_x * r.step;
        r.ray_y += r.dir_y * r.step;
        *dist += r.step;
        r.map_x = (int)r.ray_x;
        r.map_y = (int)r.ray_y;
        if (r.map_y < 0 || r.map_y >= data->map.height
            || r.map_x < 0 || r.map_x >= data->map.width)
            r.hit = 1;
        else if (data->map.grid[r.map_y][r.map_x] == '1')
            r.hit = 1;
    }
    diff_x = r.ray_x - floor(r.ray_x);
    diff_y = r.ray_y - floor(r.ray_y);
    if (diff_y < r.step * 1.5 || diff_y > 1.0 - r.step * 1.5)
    {
        *side = 1;
        *wall_x = r.ray_x;
    }
    else
    {
        *side = 0;
        *wall_x = r.ray_y;
    }
    *wall_x -= floor(*wall_x);
}

static t_texture *select_wall_texture(t_data *data, int side,
        double ray_dir_x, double ray_dir_y)
{
    if (side == 0)
    {
        if (ray_dir_x > 0)
            return (&data->tex_img_ea);
        return (&data->tex_img_we);
    }
    if (ray_dir_y > 0)
        return (&data->tex_img_so);
    return (&data->tex_img_no);
}

static int get_tex_y(double tex_pos, t_texture *tex)
{
    int tex_y;

    tex_y = (int)tex_pos;
    if (tex_y < 0)
        tex_y = 0;
    if (tex_y >= tex->height)
        tex_y = tex->height - 1;
    return (tex_y);
}

static void draw_column(t_data *data, int x, double dir_angle)
{
    t_col       c;
    int         side;
    int         tex_x;
    int         tex_y;
    int         color;
    double      wall_x;
    double      ray_dir_x;
    double      ray_dir_y;
    double      step;
    double      tex_pos;
    t_texture   *tex;

    c.percent = (double)x / (double)WIN_W;
    c.ray_angle = dir_angle - (FOV / 2) + c.percent * FOV;
    find_ray_hit(data, c.ray_angle, &c.dist, &side, &wall_x);
    c.dist = c.dist * cos(c.ray_angle - dir_angle);
    if (c.dist < 0.00001)
        c.dist = 0.00001;
    c.line_height = (int)(WIN_H / c.dist);
    c.y_start = WIN_H / 2 - c.line_height / 2;
    c.y_end = WIN_H / 2 + c.line_height / 2;
    ray_dir_x = cos(c.ray_angle);
    ray_dir_y = sin(c.ray_angle);
    tex = select_wall_texture(data, side, ray_dir_x, ray_dir_y);
    tex_x = (int)(wall_x * (double)tex->width);
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= tex->width)
        tex_x = tex->width - 1;
    if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;
    step = (double)tex->height / (double)c.line_height;
    tex_pos = (c.y_start - WIN_H / 2 + c.line_height / 2) * step;
    c.y = c.y_start;
    while (c.y < c.y_end)
    {
        if (c.y >= 0 && c.y < WIN_H)
        {
            tex_y = get_tex_y(tex_pos, tex);
            color = get_texture_pixel(tex, tex_x, tex_y);
            if (side == 1)
                color = (color >> 1) & 0x7F7F7F;
            buffer_put_pixel(&data->mlx, x, c.y, color);
        }
        tex_pos += step;
        c.y++;
    }
}
*/