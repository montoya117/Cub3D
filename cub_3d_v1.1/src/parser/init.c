
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
    player->angle = 0.0;
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
    data->map_list = NULL;
    data->key_w = 0;
    data->key_a = 0;
    data->key_s = 0;
    data->key_d = 0;
    data->key_left = 0;
    data->key_right = 0;
    data->explosion.active = 0;
    data->explosion.frame = 0;
    data->explosion.x = 0;
    data->explosion.y = 0;
    data->explosion.delay = 0;
    data->explosion.tick = 0;
    data->sprite_w = 0;
    data->sprite_h = 0;
    data->explosion.sprite_w = 0;
    data->explosion.sprite_h = 0;
    init_map(&data->map);
    init_player(&data->player);
}
