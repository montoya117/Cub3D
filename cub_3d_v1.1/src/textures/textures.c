
#include "cub_3d.h"

int load_one_texture(t_data *data, t_texture *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, path,
            &tex->width, &tex->height);
    if (!tex->img)
        return (print_error("No se pudo cargar textura"));
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
            &tex->line_len, &tex->endian);
    if (!tex->addr)
        return (print_error("No se pudo obtener data_addr de textura"));
    return (0);
}

int load_textures(t_data *data)
{
    if (load_one_texture(data, &data->tex_img_no, data->tex_path_no) != 0)
        return (1);
    if (load_one_texture(data, &data->tex_img_so, data->tex_path_so) != 0)
        return(1);
    if (load_one_texture(data, &data->tex_img_we, data->tex_path_we) != 0)
        return (1);
    if (load_one_texture(data, &data->tex_img_ea, data->tex_path_ea) != 0)
        return (1);
    return (0);
}

int get_texture_pixel(t_texture *tex, int x, int y)
{
    char    *pixel;

    pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return (*(unsigned int *)pixel);
}
