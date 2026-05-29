
#include "cub_3d.h"

#define PLAYER_RADIUS 0.05
#define MOVE_SPEED 0.04   // Ajusta la velocidad 
#define ROT_SPEED 0.04

int	is_wall(double x, double y, t_data *data)
{
	int		ix;
	int		iy;
	char	cell;

	ix = (int)x;
	iy = (int)y;
	if (ix < 0 || iy < 0 || ix >= data->map.width || iy >= data->map.height)
		return (1);
	cell = data->map.grid[iy][ix];
	return (cell != '0'); // true si NO es suelo
}

// Comprueba esquinas del círculo jugador
int	can_move(double new_x, double new_y, t_data *data)
{
	double	r;
	int		result;

	r = PLAYER_RADIUS;
	result
		= !is_wall(new_x + r, new_y + r, data)
		&& !is_wall(new_x - r, new_y + r, data)
		&& !is_wall(new_x + r, new_y - r, data)
		&& !is_wall(new_x - r, new_y - r, data);
	return (result);
}

void	check_and_move(double new_x, double new_y, t_data *data)
{
	if (can_move(new_x, new_y, data))
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	else if (!data->explosion.active)
	{
		data->explosion.active = 1;
		data->explosion.frame = 0;
		data->explosion.x = new_x;
		data->explosion.y = new_y;
		data->explosion.delay = 1;
		data->explosion.tick = 0;
	}
}

// ---- FUNCIONES SEPARADAS PARA GIRO Y MOVIMIENTO ----
void	rotate_player(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->player.angle -= ROT_SPEED;
	else if (keycode == KEY_RIGHT)
		data->player.angle += ROT_SPEED;
	// si iel angulo supera pi o -pi, lo reseta para evitar errores
	if (data->player.angle > M_PI)
		data->player.angle -= 2 * M_PI;
	if (data->player.angle < -M_PI)
		data->player.angle += 2 * M_PI;
}

static void	move_forward_backward(int keycode, t_data *data)
{
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	if (keycode == KEY_W)
	{
		dx = cos(data->player.angle) * MOVE_SPEED;
		dy = sin(data->player.angle) * MOVE_SPEED;
	}
	else if (keycode == KEY_S)
	{
		dx = -cos(data->player.angle) * MOVE_SPEED;
		dy = -sin(data->player.angle) * MOVE_SPEED;
	}
	check_and_move(data->player.pos_x + dx, data->player.pos_y + dy, data);
}

// Movimiento lateral
static void	move_sideways(int keycode, t_data *data)
{
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	if (keycode == KEY_A)
	{
		dx = sin(data->player.angle) * MOVE_SPEED;
		dy = -cos(data->player.angle) * MOVE_SPEED;
	}
	else if (keycode == KEY_D)
	{
		dx = -sin(data->player.angle) * MOVE_SPEED;
		dy = cos(data->player.angle) * MOVE_SPEED;
	}
	check_and_move(data->player.pos_x + dx, data->player.pos_y + dy, data);
}

void	move_player(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_S)
		move_forward_backward(keycode, data);
	else if (keycode == KEY_A || keycode == KEY_D)
		move_sideways(keycode, data);
}

/*
FORMULA UNIVERSAL PARA MOVER ALGO EN UNA DIRECCION EN UN PLANO

	EJE X:  posiicion nueva = posicion vieja + cos(angulo) * velocidad
	EJE Y:  posicion nueva = pos vieha + sin(angulo) * velocidaad
*/