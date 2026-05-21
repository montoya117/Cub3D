#include "cub_3d.h"

void check_and_move(int new_x, int new_y, t_data *data)
{
	char	cell;

	cell = data->map.grid[new_y][new_x];
	if (new_x >= 0 && new_x < data->map.width &&
		new_y >= 0 && new_y < data->map.height)
		{
			if (cell == '0' || cell == 'N' ||
				cell == 'S' || cell == 'E' || cell == 'W')
			{
				data->player.pos_x = new_x;	
				data->player.pos_y = new_y;
			}
		}
}


int	handle_keypress(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->player.pos_x;
	new_y = data->player.pos_y;

	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119) // W
		new_y -= 1;
	else if (keycode == 115) // S
		new_y += 1;
	else if (keycode == 97) // A
		new_x -= 1;
	else if (keycode == 100) // D
		new_x += 1;
	check_and_move(new_x, new_y, data);
		return (0);
}