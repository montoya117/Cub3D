#include "cub_3d.h"

#define PLAYER_RADIUS 0.2

int is_wall(double x, double y, t_data *data)
{
    int		ix;
    int		iy;
	char	cell;

	iy = (int)y;
	ix = (int)x;
    if (ix < 0 || iy < 0 || ix >= data->map.width || iy >= data->map.height)
        return (1);
    cell = data->map.grid[iy][ix];
    return (cell != '0'); // true si NO es suelo (lo tiene q limpiar el parseeer)
}

// Checkea esquinas del jugador
int can_move(double new_x, double new_y, t_data *data)
{
    double r;
	r = PLAYER_RADIUS;
    if (is_wall(new_x + r, new_y + r, data))
        return 0;
    if (is_wall(new_x - r, new_y + r, data))
        return 0;
    if (is_wall(new_x + r, new_y - r, data))
        return 0;
    if (is_wall(new_x - r, new_y - r, data))
        return 0;

    return 1; // Si ninguna esquina choca podemos mover
}

void check_and_move(double new_x, double new_y, t_data *data)
{
    if (can_move(new_x, new_y, data)) {
        data->player.pos_x = new_x;
        data->player.pos_y = new_y;
    }
}


int	handle_keypress(int keycode, t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x;
	new_y = data->player.pos_y;

	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119) // W
		new_y -= 0.5;
	else if (keycode == 115) // S
		new_y += 0.5;
	else if (keycode == 97) // A
		new_x -= 0.5;
	else if (keycode == 100) // D
		new_x += 0.5;
	check_and_move(new_x, new_y, data);
		return (0);
}