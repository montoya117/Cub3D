
#include "cub_3d.h"

int    print_error(char *str)
{
    ft_putstr_fd("Error\n", 2);
    if (str)
    {
        ft_putstr_fd(str, 2);
        ft_putstr_fd("\n", 2);
    }
    return (1);
}

void free_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// free lista-enlazada
void    free_map_list(t_list *map_list)
{
    t_list  *tmp;

    while (map_list)
    {
        tmp = map_list;
        map_list = map_list->next;
        free(tmp->content);
        free(tmp);
    }
}

void free_graphics(t_data *data)
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
#ifdef __linux__
    mlx_destroy_display(data->mlx.mlx_ptr);
    free(data->mlx.mlx_ptr);
#endif
}

void free_data(t_data *data)
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
