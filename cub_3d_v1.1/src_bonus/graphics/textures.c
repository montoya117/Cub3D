/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:22:08 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:22:10 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

int	load_one_texture(t_data *data, t_texture *tex, char *path)
{
	if (!path)
		return (print_error("La ruta de la textura es NULL (Fallo de parser)"));
	tex->img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		ft_putstr_fd("Ruta problemática: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (print_error("No se pudo cargar el archivo XPM."));
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (print_error("No se pudo obtener data_addr de textura"));
	return (0);
}

int	load_textures(t_data *data)
{
	if (load_one_texture(data, &data->tex_img_no, data->tex_path_no) != 0)
		return (1);
	if (load_one_texture(data, &data->tex_img_so, data->tex_path_so) != 0)
		return (1);
	if (load_one_texture(data, &data->tex_img_we, data->tex_path_we) != 0)
		return (1);
	if (load_one_texture(data, &data->tex_img_ea, data->tex_path_ea) != 0)
		return (1);
	return (0);
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}
