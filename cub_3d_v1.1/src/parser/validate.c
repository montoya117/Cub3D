
#include "cub_3d.h"

/*

2. Paso 1: check_elements
Verifica de forma estricta que no falte ningún parámetro de la configuración inicial.
FUNCIÓN check_elements(data):
    SI data->tex_no es NULL O data->tex_so es NULL O 
       data->tex_we es NULL O data->tex_ea es NULL:
        IMPRIMIR_ERROR("Faltan identificadores de textura esenciales")
        RETORNAR (1)

    SI data->color_f es -1 O data->color_c es -1:
        IMPRIMIR_ERROR("Faltan los colores de techo o suelo")
        RETORNAR (1)

    SI data->config_count NO ES 6:
        IMPRIMIR_ERROR("Número de elementos de configuración incorrecto")
        RETORNAR (1)

    RETORNAR (0) // Elementos OK
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
FUNCIÓN check_player(data):
    VARIABLE y = 0
    VARIABLE x = 0

    MIENTRAS data->map.grid[y] NO SEA NULL:
        x = 0
        MIENTRAS data->map.grid[y][x] NO SEA '\0':
            VARIABLE caracter = data->map.grid[y][x]
            
            SI caracter es 'N' O caracter es 'S' O caracter es 'E' O caracter es 'W':
                // Si data->player.dir ya se había rellenado, significa que hay otro jugador
                SI data->player.dir NO ES '\0':
                    IMPRIMIR_ERROR("El mapa contiene múltiples jugadores")
                    RETORNAR (1)
                
                // Guardamos la posición sumando 0.5 para centrarlo en la celda
                data->player.pos_x = x + 0.5
                data->player.pos_y = y + 0.5
                data->player.dir = caracter
                
                // ¡Crucial! Reemplazamos la letra por un suelo para homogeneizar el mapa
                data->map.grid[y][x] = '0'
            
            x++
        y++

    // Al salir del bucle completo, si no se encontró orientación, es que no hay jugador
    SI data->player.dir ES '\0':
        IMPRIMIR_ERROR("No se ha encontrado la posición del jugador")
        RETORNAR (1)

    RETORNAR (0) // Jugador único y guardado correctamente
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

4. Paso 3: check_walls y el algoritmo de inundación
Aquí gestionamos el clon del mapa para que la recursividad no destruya tus datos de juego.
FUNCIÓN check_walls(data):
    // Duplicamos el mapa usando la función auxiliar
    VARIABLE temp_grid = duplicate_matrix(data->map.grid, data->map.height)
    SI temp_grid es NULL:
        IMPRIMIR_ERROR("Malloc error al duplicar mapa de validación")
        RETORNAR (1)

    // Extraemos la posición entera para el Flood Fill
    VARIABLE p_x = PARTE_ENTERA(data->player.pos_x)
    VARIABLE p_y = PARTE_ENTERA(data->player.pos_y)

    // Lanzamos la inundación recursiva
    VARIABLE mapa_abierto = flood_fill(temp_grid, p_x, p_y, data)

    // Liberamos SIEMPRE la matriz clonada inmediatamente para evitar leaks
    free_matrix(temp_grid, data->map.height)

    SI mapa_abierto ES 1:
        IMPRIMIR_ERROR("El mapa está abierto / No está rodeado por muros")
        RETORNAR (1)

    RETORNAR (0) // Muros herméticos

El motor recursivo: flood_fill
FUNCIÓN flood_fill(temp_grid, x, y, data):
    // Caso de error 1: Nos salimos de los límites de la matriz alto/bajo
    SI y < 0 O y >= data->map.height:
        RETORNAR (1)

    // Caso de error 2: Nos salimos del límite de longitud de esta fila en concreto
    SI x < 0 O x >= LONGITUD_STRING(temp_grid[y]):
        RETORNAR (1)

    // Caso de error 3: Si tocamos un espacio vacío o un fin de línea, el mapa gotea
    SI temp_grid[y][x] ES ' ' O temp_grid[y][x] ES '\0':
        RETORNAR (1)

    // Caso base seguro: Si tocamos un muro ('1') o una zona validada ('V'), nos frenamos
    SI temp_grid[y][x] ES '1' O temp_grid[y][x] ES 'V':
        RETORNAR (0)

    // Marcamos la celda actual como Visitada ('V')
    temp_grid[y][x] = 'V'

    // Inundamos recursivamente en cruz (Norte, Sur, Oeste, Este)
    SI flood_fill(temp_grid, x, y - 1, data) ES 1 O   // Arriba
       flood_fill(temp_grid, x, y + 1, data) ES 1 O   // Abajo
       flood_fill(temp_grid, x - 1, y, data) ES 1 O   // Izquierda
       flood_fill(temp_grid, x + 1, y, data) ES 1:     // Derecha
        RETORNAR (1) // Si cualquiera de las direcciones encuentra una fuga, arrastra el error hacia arriba

    RETORNAR (0) // Todo este sector está cerrado
*/

/*

1. Conector Principal: validate_elements_and_map
Este es el director de orquesta. Llama a los tres pasos defensivos en orden. Si alguno falla, frena en seco.
FUNCIÓN validate_elements_and_map(data):
    // Paso 1: Comprobar configuración global
    SI check_elements(data) NO ES 0:
        RETORNAR (1) // Error ya impreso dentro

    // Paso 2: Buscar y configurar jugador
    SI check_player(data) NO ES 0:
        RETORNAR (1) // Error ya impreso dentro

    // Paso 3: Validar que los muros estén cerrados
    SI check_walls(data) NO ES 0:
        RETORNAR (1) // Error ya impreso dentro

    RETORNAR (0) // ¡Éxito absoluto! Todo el archivo .cub es válido

*/

int validate_elements_and_map(t_data *data)
{
    if (check_elements(data) != 0)
        return (1);
    if (check_player(data) != 0)
        return (1);
    return (0);
}

