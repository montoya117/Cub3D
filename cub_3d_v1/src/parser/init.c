
#include "cub_3d.h"

static void    init_map(t_map *map)
{
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
}

static void init_player(t_player *player)
{
    player->pos_x = 0;
    player->pos_y = 0;
    player->dir = '\0';
}

void    init_data(t_data *data)
{
    data->tex_no = NULL;
    data->tex_so = NULL;
    data->tex_we = NULL;
    data->tex_ea = NULL;
    data->color_f = -1;
    data->color_c = -1;
    data->config_count = 0;
    data->map_started = 0;

    init_map(&data->map);
    init_player(&data->player);
}
