#include "cub_3d.h"

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119) // W
		data->player.pos_y -= 1;
	else if (keycode == 115) // S
		data->player.pos_y += 1;
	else if (keycode == 97) // A
		data->player.pos_x -= 1;
	else if (keycode == 100) // D
		data->player.pos_x += 1;
	return (0);
}