/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config_textures.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:39:13 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:39:15 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

static char	**get_texture_target(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (&data->tex_path_no);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (&data->tex_path_so);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (&data->tex_path_we);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (&data->tex_path_ea);
	return (NULL);
}

int	handle_texture(char *line, t_data *data)
{
	char	**target;

	target = get_texture_target(line, data);
	if (!target)
		return (print_error("Invalid texture Id"));
	if (*target != NULL)
		return (print_error("Duplicated texture"));
	*target = ft_strtrim(&line[2], " \n\t\v\f\r");
	if (!*target)
		return (print_error("Malloc error in texture"));
	if ((*target)[0] == '\0')
	{
		free(*target);
		*target = NULL;
		return (print_error("Empty texture path"));
	}
	data->config_count++;
	return (0);
}
