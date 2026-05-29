
#include "cub_3d.h"

static void	find_ray_hit_position(t_data *data, t_ray *r)
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

static void	calc_ray_and_distance(t_data *data, t_render_ctx *ctx,
	int x, double dir_angle)
{
	ctx->c.percent = (double)x / (double)WIN_W;
	ctx->c.ray_angle = dir_angle - (FOV / 2.0) + ctx->c.percent * FOV;
	ctx->r.dir_x = cos(ctx->c.ray_angle);
	ctx->r.dir_y = sin(ctx->c.ray_angle);
	ctx->r.map_x = (int)data->player.pos_x;
	ctx->r.map_y = (int)data->player.pos_y;
	init_dda_vars(data, &ctx->r);
	find_ray_hit_position(data, &ctx->r);
	// Calculo de wall_x
	if (ctx->r.side == 0)
		ctx->r.wall_x = data->player.pos_y
			+ (ctx->r.side_dist_x - ctx->r.delta_dist_x) * ctx->r.dir_y;
	else
		ctx->r.wall_x = data->player.pos_x
			+ (ctx->r.side_dist_y - ctx->r.delta_dist_y) * ctx->r.dir_x;
	ctx->r.wall_x -= floor(ctx->r.wall_x);
	// (eevita el fish-eye)
	if (ctx->r.side == 0)
		ctx->c.dist = ctx->r.side_dist_x - ctx->r.delta_dist_x;
	else
		ctx->c.dist = ctx->r.side_dist_y - ctx->r.delta_dist_y;
	ctx->c.dist = ctx->c.dist * cos(ctx->c.ray_angle - dir_angle);
	if (ctx->c.dist < 0.00001)
		ctx->c.dist = 0.00001;
}

static void	calc_projection_and_texture(t_data *data, t_render_ctx *ctx)
{
	ctx->c.line_height = (int)(WIN_H / ctx->c.dist);
	ctx->c.y_start = WIN_H / 2 - ctx->c.line_height / 2;
	ctx->c.y_end = WIN_H / 2 + ctx->c.line_height / 2;
	ctx->d.tex = select_wall_texture(data, &ctx->r);
	ctx->d.tex_x = (int)(ctx->r.wall_x * (double)ctx->d.tex->width);
	// Control d flip seguun dir
	if ((ctx->r.side == 0 && ctx->r.dir_x > 0)
		|| (ctx->r.side == 1 && ctx->r.dir_y < 0))
		ctx->d.tex_x = ctx->d.tex->width - ctx->d.tex_x - 1;
	if (ctx->d.tex_x < 0)
		ctx->d.tex_x = 0;
	if (ctx->d.tex_x >= ctx->d.tex->width)
		ctx->d.tex_x = ctx->d.tex->width - 1;
	ctx->d.step = (double)ctx->d.tex->height / (double)ctx->c.line_height;
	ctx->d.tex_pos
		= (ctx->c.y_start - WIN_H / 2 + ctx->c.line_height / 2) * ctx->d.step;
}

static void	render_column(t_data *data, int x, t_render_ctx *ctx)
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
		// Caalculo de tex_y:
		ctx->d.tex_y = (int)ctx->d.tex_pos;
		if (ctx->d.tex_y < 0)
			ctx->d.tex_y = 0;
		if (ctx->d.tex_y >= ctx->d.tex->height)
			ctx->d.tex_y = ctx->d.tex->height - 1;
		ctx->d.color = get_texture_pixel(ctx->d.tex,
				ctx->d.tex_x, ctx->d.tex_y);
		// Sombrea paredes verticales
		if (ctx->r.side == 1)
			ctx->d.color = (ctx->d.color >> 1) & 0x7F7F7F;
		buffer_put_pixel(&data->mlx, x, ctx->c.y, ctx->d.color);
		ctx->d.tex_pos += ctx->d.step;
		ctx->c.y++;
	}
}

void	draw_column(t_data *data, int x, double dir_angle)
{
	t_render_ctx	ctx;

	memset(&ctx, 0, sizeof(ctx));
	calc_ray_and_distance(data, &ctx, x, dir_angle);
	calc_projection_and_texture(data, &ctx);
	render_column(data, x, &ctx);
}

void	draw(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		draw_column(data, x, data->player.angle);
		x++;
	}
}
