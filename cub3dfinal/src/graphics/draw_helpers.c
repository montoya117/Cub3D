/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:29:00 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:29:02 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	find_ray_hit_position(t_data *data, t_ray *r)
{
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
			break ;
		if (data->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

void	paint_ceiling(t_data *data, int x, int y_start)
{
	int	y;
	int	y_start_clamped;

	y_start_clamped = y_start;
	if (y_start_clamped < 0)
		y_start_clamped = 0;
	if (y_start_clamped > WIN_H)
		y_start_clamped = WIN_H;
	y = 0;
	while (y < y_start_clamped)
	{
		buffer_put_pixel(&data->mlx, x, y, data->color_c);
		y++;
	}
}

void	render_wall_stripe(t_data *data, int x, t_render_ctx *ctx)
{
	ctx->c.y = ctx->c.y_start;
	if (ctx->c.y < 0)
	{
		ctx->d.tex_pos += ctx->d.step * (-ctx->c.y);
		ctx->c.y = 0;
	}
	if (ctx->c.y_end > WIN_H)
		ctx->c.y_end = WIN_H;
	while (ctx->c.y < ctx->c.y_end)
	{
		ctx->d.tex_y = (int)ctx->d.tex_pos;
		if (ctx->d.tex_y < 0)
			ctx->d.tex_y = 0;
		if (ctx->d.tex_y >= ctx->d.tex->height)
			ctx->d.tex_y = ctx->d.tex->height - 1;
		ctx->d.color = get_texture_pixel(ctx->d.tex,
				ctx->d.tex_x, ctx->d.tex_y);
		if (ctx->r.side == 1)
			ctx->d.color = (ctx->d.color >> 1) & 0x7F7F7F;
		buffer_put_pixel(&data->mlx, x, ctx->c.y, ctx->d.color);
		ctx->d.tex_pos += ctx->d.step;
		ctx->c.y++;
	}
}

void	paint_floor(t_data *data, int x, int y_end)
{
	int	y;
	int	y_end_clamped;

	y_end_clamped = y_end;
	if (y_end_clamped < 0)
		y_end_clamped = 0;
	if (y_end_clamped > WIN_H)
		y_end_clamped = WIN_H;
	y = y_end_clamped;
	while (y < WIN_H)
	{
		buffer_put_pixel(&data->mlx, x, y, data->color_f);
		y++;
	}
}

void	render_column(t_data *data, int x, t_render_ctx *ctx)
{
	paint_ceiling(data, x, ctx->c.y_start);
	render_wall_stripe(data, x, ctx);
	paint_floor(data, x, ctx->c.y_end);
}
