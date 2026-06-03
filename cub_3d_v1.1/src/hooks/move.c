/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:36:26 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:36:37 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	is_wall(double x, double y, t_data *data)
{
	int		ix;
	int		iy;
	char	cell;

	ix = (int)x;
	iy = (int)y;
	if (ix < 0 || iy < 0 || ix >= data->map.width || iy >= data->map.height)
		return (1);
	cell = data->map.grid[iy][ix];
	return (cell != '0');
}

int	can_move(double new_x, double new_y, t_data *data)
{
	double	r;
	int		result;

	r = PLAYER_RADIUS;
	result
		= !is_wall(new_x + r, new_y + r, data)
		&& !is_wall(new_x - r, new_y + r, data)
		&& !is_wall(new_x + r, new_y - r, data)
		&& !is_wall(new_x - r, new_y - r, data);
	return (result);
}

void	check_and_move(double new_x, double new_y, t_data *data)
{
	if (can_move(new_x, new_y, data))
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	else if (!data->explosion.active)
	{
		data->explosion.active = 1;
		data->explosion.frame = 0;
		data->explosion.x = new_x;
		data->explosion.y = new_y;
		data->explosion.delay = 1;
		data->explosion.tick = 0;
	}
}

void	rotate_player(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->player.angle -= ROT_SPEED;
	else if (keycode == KEY_RIGHT)
		data->player.angle += ROT_SPEED;
	if (data->player.angle > M_PI)
		data->player.angle -= 2 * M_PI;
	if (data->player.angle < -M_PI)
		data->player.angle += 2 * M_PI;
}

void	move_player(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_S)
		move_forward_backward(keycode, data);
	else if (keycode == KEY_A || keycode == KEY_D)
		move_sideways(keycode, data);
}
