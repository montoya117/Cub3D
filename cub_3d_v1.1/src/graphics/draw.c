
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
struct ——>>
typedef struct s_draw_data
{
    t_texture   *tex;
    int         tex_x;
    int         tex_y;
    double      step;
    double      tex_pos;
    int         color;
}   t_draw_data;

static void init_dda_vars(t_data *data, t_ray *r)
{
    r->delta_dist_x = (r->dir_x == 0) ? 1e30 : fabs(1.0 / r->dir_x);
    r->delta_dist_y = (r->dir_y == 0) ? 1e30 : fabs(1.0 / r->dir_y);
    r->map_x = (int)data->player.pos_x;
    r->map_y = (int)data->player.pos_y;
    if (r->dir_x < 0)
    {
        r->step_x = -1;
        r->side_dist_x = (data->player.pos_x - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1;
        r->side_dist_x = (r->map_x + 1.0 - data->player.pos_x) * r->delta_dist_x;
    }
    if (r->dir_y < 0)
    {
        r->step_y = -1;
        r->side_dist_y = (data->player.pos_y - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1;
        r->side_dist_y = (r->map_y + 1.0 - data->player.pos_y) * r->delta_dist_y;
    }
}

static void find_ray_hit(t_data *data, t_ray *r)
{
    init_dda_vars(data, r);
    r->hit = 0;
    while (!r->hit)
    {
        if (r->side_dist_x < r->side_dist_y)
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x;
            r->side = 0;
        }
        else
        {
            r->side_dist_y += r->delta_dist_y;
            r->map_y += r->step_y;
            r->side = 1;
        }
        if (r->map_y < 0 || r->map_y >= data->map.height
            || r->map_x < 0 || r->map_x >= data->map.width)
            break;
        if (data->map.grid[r->map_y][r->map_x] == '1')
            r->hit = 1;
    }
    r->wall_x = (r->side == 0) ? (data->player.pos_y + (r->side_dist_x - r->delta_dist_x) * r->dir_y)
                               : (data->player.pos_x + (r->side_dist_y - r->delta_dist_y) * r->dir_x);
    r->wall_x -= floor(r->wall_x);
}

static t_texture *select_wall_texture(t_data *data, t_ray *r)
{
    if (r->side == 0)
    {
        if (r->dir_x > 0)
            return (&data->tex_img_ea);
        return (&data->tex_img_we);
    }
    if (r->dir_y > 0)
        return (&data->tex_img_so);
    return (&data->tex_img_no);
}

void draw_column(t_data *data, int x, double dir_angle)
{
    t_col       c;
    t_ray       r;
    t_draw_data d;

    // 1. Inicialización del Rayo
    c.percent = (double)x / (double)WIN_W;
    c.ray_angle = dir_angle - (FOV / 2.0) + c.percent * FOV;
    r.dir_x = cos(c.ray_angle);
    r.dir_y = sin(c.ray_angle);

    // 2. Ejecución de la Física (DDA)
    find_ray_hit(data, &r);
    c.dist = (r.side == 0) ? (r.side_dist_x - r.delta_dist_x) : (r.side_dist_y - r.delta_dist_y);

    // 3. Proyección de la Columna (Pantalla)
    c.dist = c.dist * cos(c.ray_angle - dir_angle);
    if (c.dist < 0.00001)
        c.dist = 0.00001;
    c.line_height = (int)(WIN_H / c.dist);
    c.y_start = WIN_H / 2 - c.line_height / 2;
    c.y_end = WIN_H / 2 + c.line_height / 2;

    // 4. Configuración del Mapeo de Texturas
    d.tex = select_wall_texture(data, &r);
    d.tex_x = (int)(r.wall_x * (double)d.tex->width);
    if ((r.side == 0 && r.dir_x > 0) || (r.side == 1 && r.dir_y < 0))
        d.tex_x = d.tex->width - d.tex_x - 1;
    d.step = (double)d.tex->height / (double)c.line_height;
    d.tex_pos = (c.y_start - WIN_H / 2 + c.line_height / 2) * d.step;

    // 5. Ajuste y Renderizado Vertical
    c.y = c.y_start;
    if (c.y < 0)
    {
        d.tex_pos += d.step * (-c.y);
        c.y = 0;
    }
    if (c.y_end > WIN_H)
        c.y_end = WIN_H;
    while (c.y < c.y_end)
    {
        d.tex_y = (int)d.tex_pos & (d.tex->height - 1);
        d.color = get_texture_pixel(d.tex, d.tex_x, d.tex_y);
        if (r.side == 1)
            d.color = (d.color >> 1) & 0x7F7F7F;
        buffer_put_pixel(&data->mlx, x, c.y, d.color);
        d.tex_pos += d.step;
        c.y++;
    }
}

*/