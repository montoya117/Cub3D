
#include "cub_3d.h"

/*

2. Paso 1: check_elements
Verifica de forma estricta que no falte ningún parámetro de la configuración inicial.
*/
int check_elements(t_data *data)
{
    if (data->tex_no == NULL || data->tex_so == NULL || data->tex_we == NULL || data->tex_ea == NULL)
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
    !! MIRAR ✅
    aprovechar el bucle de check_player (o hacer otra función pequeña) para verificar 
    que data->map.grid[y][x] sea únicamente un espacio ' ', un muro '1', un suelo '0' o una letra de jugador. 
    Si encuentras algo ajeno, devuelves error. Si dejas pasar caracteres raros, el raycaster podría volverse loco después.
*/

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
El motor recursivo: flood_fill
FUNCIÓN flood_fill(temp_grid, x, y, data):
  
*/

int flood_fill(char **tmp_grid, int col, int row, t_data *data)
{
    // 1. Si el algoritmo se sale de los límites de la matriz -> El mapa está abierto (Error)
    if (row < 0 || row >= data->map.height || col < 0 || col >= data->map.width)
        return (1);    
    // 2. Si la inundación toca un espacio vacío o un fin de línea -> El mapa está abierto (Error)
    if (tmp_grid[row][col] == ' ' || tmp_grid[row][col] == '\0')
        return (1);
    // 3. Si toca un muro ('1') o una zona ya verificada ('V'), el camino está a salvo. Nos detenemos.
    if (tmp_grid[row][col] == '1' || tmp_grid[row][col] == 'V')
        return (0);
    // 4. Marcamos la celda actual como Visitada ('V') para no entrar en bucle infinito
    tmp_grid[row][col] = 'V';
    // 5. LLamamos recursivamente flood_fill arriba abajo y a los lados. Si cualquiera se escapa, devuelve 1.
    if (flood_fill(tmp_grid, col, row -1 , data)
        || flood_fill(tmp_grid, col + 1, row, data)
        || flood_fill(tmp_grid, col, row +1, data)
        || flood_fill(tmp_grid, col - 1,row, data))
        return (1);
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
    if (check_walls(data) != 0)
        return (1);
    return (0);
}
