
#include "cub_3d.h"

/*

2. Paso 1: check_elements
Verifica de forma estricta que no falte ningún parámetro de la configuración inicial.
*/
int check_elements(t_data *data)
{
    if (data->tex_path_no == NULL || data->tex_path_so == NULL || data->tex_path_we == NULL || data->tex_path_ea == NULL)
        return(print_error("Faltan identificadores de textura esenciales"));
    if (data->color_c == -1 || data->color_f == -1)
        return (print_error("Faltan los colores de techo o suelo"));
    if (data->config_count != 6)
        return (print_error("Número de elementos de configuración incorrecto"));
    return (0);
}

/*

3. Paso 2: check_player
Rastrea la matriz completa buscando la letra del jugador para inicializar sus coordenadas y limpiar el mapa.

*/
int check_player(t_data *data)
{
    int     y;
    int     x;
    char    c;

    if (!data->map.grid)
        return (print_error("No se puede validar el jugador: la matriz del mapa esta vacia"));
    y = 0;
    x = 0;
    while(data->map.grid[y] != NULL)
    {
        x = 0;
        while (data->map.grid[y][x] != '\0')
        {
            c = data->map.grid[y][x];
            // check cosas que no tocan!
            if (c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != '0' && c != '1' && c != ' ')
                return (print_error("El mapa contiene caracteres no permitidos"));
            if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
            {
                if (data->player.dir != '\0')
                    return (print_error("El mapa contiene múltiples jugadores"));
                data->player.pos_x = (double)x + 0.5;
                data->player.pos_y = (double)y + 0.5;
                data->player.dir = c;
                // remplazamos dir por un '0' para hacer mapa viable
                data->map.grid[y][x] = '0';
            }
            x++;
        }
        y++;
    }
    if (data->player.dir == '\0')
        return (print_error("No se ha encontrado la posición del jugador"));
    return (0);
}

/*
TODO
*/

int check_all_floors_closed(t_data *data)
{
    int row;
    int col;

    row = 0;
    while (row < data->map.height)
    {
        col = 0;
        while (col < data->map.width)
        {
            if (data->map.grid[row][col] == '0')
            {
                if (is_open_floor(data, row , col))
                    return (print_error("El mapa contiene espacios internos inválidos"));
            }
            col++;
        }
        row++;
    }
    return (0);
}

/*
4. Paso 3: check_walls y el algoritmo de inundación
Aquí gestionamos el clon del mapa para que la recursividad no destruya tus datos de juego.
FUNCIÓN check_walls(data):
*/

int check_walls(t_data *data)
{
    char    **tmp_grid;
    int     is_open; // flag para el return de flood_fill si devuelve 1 el mapa esta mal...

    // Duplicamos el grid del mapa (necesitarás programar tu función auxiliar de clonar matrices)
    tmp_grid = duplicate_matrix(data->map.grid, data->map.height);
    if (!tmp_grid)
        return (print_error("Malloc error al duplicar mapa de validación"));
    // Lanzamos la flood_fill desde la posición entera donde estaba el jugador
    is_open = flood_fill(tmp_grid, (int)data->player.pos_x, (int)data->player.pos_y, data);
    // Liberamos la matriz temporal pase lo que pase para evitar leaks catastróficos
    free_matrix(tmp_grid, data->map.height);
    if (is_open) // si flood fill retorna 1 es error...
        return (print_error("El mapa está abierto / No está completamente rodeado por muros"));
    return (0);
}

/*

1. Conector Principal: validate_elements_and_map
Este es el director de orquesta. Llama a los tres pasos defensivos en orden. Si alguno falla, frena en seco.
*/

int validate_elements_and_map(t_data *data)
{
    if (check_elements(data) != 0)
        return (1);
    if (check_player(data) != 0)
        return (1);
    if (check_all_floors_closed(data) != 0)
        return (1);
    if (check_walls(data) != 0)
        return (1);
    return (0);
}
