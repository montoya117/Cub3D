/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadelgad <jadelgad@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 11:40:44 by jadelgad          #+#    #+#             */
/*   Updated: 2026/06/03 11:40:45 by jadelgad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_3d.h"

// free lista-enlazada
void	free_map_list(t_list *map_list)
{
	t_list	*tmp;

	while (map_list)
	{
		tmp = map_list;
		map_list = map_list->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_graphics(data);
	free(data->tex_path_no);
	free(data->tex_path_so);
	free(data->tex_path_we);
	free(data->tex_path_ea);
	data->tex_path_no = NULL;
	data->tex_path_so = NULL;
	data->tex_path_we = NULL;
	data->tex_path_ea = NULL;
	if (data->map.grid)
	{
		free_matrix(data->map.grid, data->map.height);
		data->map.grid = NULL;
	}
	if (data->map_list)
	{
		free_map_list(data->map_list);
		data->map_list = NULL;
	}
}
