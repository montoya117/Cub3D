
#include "cub_3d.h"

void	buffer_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	pos;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	pos = (y * mlx->size_line) + (x * (mlx->bpp / 8));
	*(unsigned int *)(mlx->img_data + pos) = color;
}
	/*para saber en que byte esta el pixel:
	cada linea ocupa mlx->sizebytes y cada pixelw mlx->bpp/8
	la pos final es:
	(bytes hasta la fila y) + (bytes en la comuna x en esta fila)*/

void	clear_img_buffer(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			buffer_put_pixel(mlx, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
