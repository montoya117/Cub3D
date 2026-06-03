/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:30:33 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:30:36 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

void	process_movement(t_data *data)
{
	if (data->key_w)
		move_player(KEY_W, data);
	if (data->key_a)
		move_player(KEY_A, data);
	if (data->key_s)
		move_player(KEY_S, data);
	if (data->key_d)
		move_player(KEY_D, data);
	if (data->key_left)
		rotate_player(KEY_LEFT, data);
	if (data->key_right)
		rotate_player(KEY_RIGHT, data);
}
