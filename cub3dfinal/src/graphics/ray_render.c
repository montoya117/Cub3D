/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:21:44 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:21:46 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	set_delta_dist(r);
	r->map_x = (int)data->player.pos_x;
	r->map_y = (int)data->player.pos_y;
	set_steps_and_side_dists(data, r);
}

t_texture	*select_wall_texture(t_data *data, t_ray *r)
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
