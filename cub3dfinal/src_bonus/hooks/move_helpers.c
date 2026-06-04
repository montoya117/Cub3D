/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:36:43 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:36:49 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	move_forward_backward(int keycode, t_data *data)
{
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	if (keycode == KEY_W)
	{
		dx = cos(data->player.angle) * MOVE_SPEED;
		dy = sin(data->player.angle) * MOVE_SPEED;
	}
	else if (keycode == KEY_S)
	{
		dx = -cos(data->player.angle) * MOVE_SPEED;
		dy = -sin(data->player.angle) * MOVE_SPEED;
	}
	check_and_move(data->player.pos_x + dx, data->player.pos_y + dy, data);
}

void	move_sideways(int keycode, t_data *data)
{
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	if (keycode == KEY_A)
	{
		dx = sin(data->player.angle) * MOVE_SPEED;
		dy = -cos(data->player.angle) * MOVE_SPEED;
	}
	else if (keycode == KEY_D)
	{
		dx = -sin(data->player.angle) * MOVE_SPEED;
		dy = cos(data->player.angle) * MOVE_SPEED;
	}
	check_and_move(data->player.pos_x + dx, data->player.pos_y + dy, data);
}
