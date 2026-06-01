#include "cub_3d.h"

void	init_ray_base(t_ray *r)
{
	r->dir_x = 0.0;
	r->dir_y = 0.0;
	r->map_x = 0;
	r->map_y = 0;
	r->delta_dist_x = 0.0;
	r->delta_dist_y = 0.0;
	r->side_dist_x = 0.0;
	r->side_dist_y = 0.0;
	r->step_x = 0;
	r->step_y = 0;
	r->hit = 0;
	r->side = 0;
	r->wall_x = 0.0;
}

static void	set_delta_dist(t_ray *r)
{
	if (r->dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->dir_x);
	if (r->dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->dir_y);
}

// inicializa pasos y distancias laterales para DDA
static void	set_steps_and_side_dists(t_data *data, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (data->player.pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x
			= (r->map_x + 1.0 - data->player.pos_x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (data->player.pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y
			= (r->map_y + 1.0 - data->player.pos_y) * r->delta_dist_y;
	}
}

void	init_dda_vars(t_data *data, t_ray *r)
{
	// 1. Calcula laas deltas
	set_delta_dist(r);
	// 2. Inicializa casilla del mapa donde empieza el rayo
	r->map_x = (int)data->player.pos_x;
	r->map_y = (int)data->player.pos_y;
	// 3. Calcula pasos e inicializa distancias laterales
	set_steps_and_side_dists(data, r);
}

t_texture	*select_wall_texture(t_data *data, t_ray *r)
{
	if (r->side == 0) // es pared horizontal X
	{
		if (r->dir_x > 0)
			return (&data->tex_img_ea);
		return (&data->tex_img_we);
	}
	if (r->dir_y > 0) // es pared vertical Y
		return (&data->tex_img_so);
	return (&data->tex_img_no);
}

/*
---> refactorizacion draw_column
void init_draw_data(t_data *data, t_draw_data *d, t_ray *r, t_col *c)
{
	d->tex = select_wall_texture(data, r);
	d->tex_x = (int)(r->wall_x * (double)d->tex->width);
	if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
	{
		d->tex_x = d->tex->width - d->tex_x - 1;
	}
	d->step = (double)d->tex->height / (double)c->line_height;
	d->tex_pos = (c->y_start - WIN_H / 2 + c->line_height / 2) * d->step;
	d->color = 0;
}

*/