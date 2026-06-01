#include "cub_3d.h"

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir = '\0';
	player->angle = 0.0;
}

void	init_texture(t_texture *tex)
{
	tex->img = NULL;
	tex->addr = NULL;
	tex->width = 0;
	tex->height = 0;
	tex->bpp = 0;
	tex->line_len = 0;
	tex->endian = 0;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img_ptr = NULL;
	mlx->img_data = NULL;
	mlx->bpp = 0;
	mlx->size_line = 0;
	mlx->endian = 0;
}
