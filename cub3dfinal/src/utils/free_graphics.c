/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:40:52 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:40:53 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

#ifdef __linux__

static void	destroy_mlx(t_data *data)
{
	if (!data->mlx.mlx_ptr)
		return ;
	mlx_destroy_display(data->mlx.mlx_ptr);
	free(data->mlx.mlx_ptr);
	data->mlx.mlx_ptr = NULL;
}

#else

static void	destroy_mlx(t_data *data)
{
	if (!data->mlx.mlx_ptr)
		return ;
	free(data->mlx.mlx_ptr);
	data->mlx.mlx_ptr = NULL;
}

#endif

void	free_graphics(t_data *data)
{
	if (!data->mlx.mlx_ptr)
		return ;
	if (data->tex_img_no.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_img_no.img);
	if (data->tex_img_so.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_img_so.img);
	if (data->tex_img_we.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_img_we.img);
	if (data->tex_img_ea.img)
		mlx_destroy_image(data->mlx.mlx_ptr, data->tex_img_ea.img);
	if (data->mlx.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	if (data->mlx.win_ptr)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	destroy_mlx(data);
}
