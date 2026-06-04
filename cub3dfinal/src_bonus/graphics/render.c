/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:21:54 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:21:58 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	render(t_data *data)
{
	process_movement(data);
	update_explosion_anim(data);
	clear_img_buffer(&data->mlx);
	draw(data);
	draw_explosion_in_buffer(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.win_ptr, data->mlx.img_ptr, 0, 0);
	draw_minimap_buffer(data);
	return (0);
}
