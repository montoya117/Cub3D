
#include "cub_3d.h"

#define PLAYER_RADIUS 0.05
#define MOVE_SPEED 0.04   // Ajusta la velocidad 
#define ROT_SPEED 0.04

int is_wall(double x, double y, t_data *data)
{
    int ix;
    int iy;

    ix = (int)x;
    iy = (int)y;
    if (ix < 0 || iy < 0 || ix >= data->map.width || iy >= data->map.height)
        return 1;
    char cell = data->map.grid[iy][ix];
    return (cell != '0'); // true si NO es suelo
}

// Comprueba esquinas del círculo jugador
int can_move(double new_x, double new_y, t_data *data)
{
    double r;
    int result;

    r = PLAYER_RADIUS;
    result =
        !is_wall(new_x + r, new_y + r, data) &&
        !is_wall(new_x - r, new_y + r, data) &&
        !is_wall(new_x + r, new_y - r, data) &&
        !is_wall(new_x - r, new_y - r, data);
    return (result);
}

void check_and_move(double new_x, double new_y, t_data *data)
{
    if (can_move(new_x, new_y, data)) {
        data->player.pos_x = new_x;
        data->player.pos_y = new_y;
    }
    else
    {
        printf("Activando animacion en (%.2f, %.2f)\n", new_x, new_y);
        data->explosion.active = 1;
        data->explosion.frame = 0;
        data->explosion.x = new_x;
        data->explosion.y = new_y;
        data->explosion.delay = 2; // para depurar más visible
        data->explosion.tick = 0;
    }
}

// ---- FUNCIONES SEPARADAS PARA GIRO Y MOVIMIENTO ----

void rotate_player(int keycode, t_data *data)
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

void move_player(int keycode, t_data *data)
{
    double new_x;
    double new_y;
    
    new_x = data->player.pos_x;
    new_y= data->player.pos_y;

    // Movimiento relativo donde miro (angle)
    if (keycode == KEY_W)
    { // 'W': adelante
        new_x += cos(data->player.angle) * MOVE_SPEED;
        new_y += sin(data->player.angle) * MOVE_SPEED;
    }
    else if (keycode == KEY_S)
    { // 'S': atrás
        new_x -= cos(data->player.angle) * MOVE_SPEED;
        new_y -= sin(data->player.angle) * MOVE_SPEED;
    }
    else if (keycode == KEY_A)
    { // 'A': strafe izquierda
        new_x += sin(data->player.angle) * MOVE_SPEED;
        new_y -= cos(data->player.angle) * MOVE_SPEED;
    }
    else if (keycode == KEY_D)
    { // 'D': strafe derecha
        new_x -= sin(data->player.angle) * MOVE_SPEED;
        new_y += cos(data->player.angle) * MOVE_SPEED;
    }
    check_and_move(new_x, new_y, data);
}
/*
FORMULA UNIVERSAL PARA MOVER ALGO EN UNA DIRECCION EN UN PLANO

    EJE X:  posiicion nueva = posicion vieja + cos(angulo) * velocidad
    EJE Y:  posicion nueva = pos vieha + sin(angulo) * velocidaad
*/