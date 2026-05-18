
#include "cub_3d.h"

/*
    - is_map_line: Detecta si la línea contiene solo 01NSEW y espacios.
    - save_map_line: Guarda la línea temporalmente (en una lista o un string acumulado).
    - convert_list_to_array: Transforma lo guardado en el char **grid final.
*/

/*

1. Pseudocódigo de is_map_line
Esta función solo debe decir "sí" o "no" (1 o 0). Su único objetivo es verificar que la línea no tenga caracteres prohibidos.
FUNCIÓN is_map_line(linea):
    VARIABLE i = 0

    SI linea es NULL o linea está vacía o es solo un salto de línea:
        RETORNAR (0)  // No es una línea de mapa válida

    MIENTRAS exista linea[i]:
        SI linea[i] NO ES UN ESPACIO (' ') Y
           linea[i] NO ES UN SUELO ('0') Y
           linea[i] NO ES UN MURO ('1') Y
           linea[i] NO ES UNA POSICIÓN DEL JUGADOR ('N', 'S', 'E', 'W'):
               RETORNAR (0) // Encontró un carácter inválido (ej. 'X', 'A', etc.)
        i++

    RETORNAR (1) // Toda la línea contiene solo caracteres permitidos

*/

int is_map_line(char *line)
{
    int i;

    if (!line || line[0] == '\0')
        return (0); // not valid
    i = 0;
    while (line[i] != '\0')
    {
        if (line[i] != ' '  && line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
            return (0);
        i++;
    }
    return (1);
}

/*
2. Pseudocódigo de save_map_line
Aquí usamos las funciones de tu libft (ft_lstnew y ft_lstadd_back).
FUNCIÓN save_map_line(linea_limpia, data):
    1. Activar el estado de que el mapa ya empezó:
       data->map_started = 1

    2. Duplicar la línea para asegurarnos la memoria:
       VARIABLE linea_duplicada = ft_strdup(linea_limpia)
       SI linea_duplicada es NULL -> RETORNAR ERROR

    3. Crear el nuevo nodo usando tu libft:
       VARIABLE nuevo_nodo = ft_lstnew(linea_duplicada)
       SI nuevo_nodo es NULL:
           Liberar linea_duplicada
           RETORNAR ERROR

    4. Añadir el nodo al final de tu lista acumulada usando tu libft:
       ft_lstadd_back(&(data->map_list), nuevo_nodo)

    5. Incrementar el contador de filas de tu mapa:
       data->map.height++

    RETORNAR (0) // Éxito
*/
int save_map_line(char *valid_line, t_data *data)
{
    char    *line_copy;
    t_list  *new_node;
    int     len;
    
    data->map_started = 1;
    line_copy = ft_strdup(valid_line);
    if (!line_copy)
        return (print_error("Malloc error in map"));
    new_node = ft_lstnew(line_copy);
    if (!new_node)
    {
        free(line_copy);
        return (print_error("Malloc nodes map error"));
    }
    ft_lstadd_back(&(data->map_list), new_node);
    data->map.height++;
    len = ft_strlen(valid_line);
    if (len > data->map.width)
        data->map.width = len;
    
    return (0);
}

/*
3. Pseudocódigo de convert_list_to_array
Esta función se ejecuta al terminar el GNL. Transforma la lista enlazada temporal en el char **grid final.
FUNCIÓN convert_list_to_array(data):
    SI data->map_list es NULL o data->map.height == 0:
        RETORNAR ERROR ("Archivo sin mapa")

    1. Reservar memoria para la matriz (filas + 1 para el NULL de cierre):
       data->map.grid = malloc(sizeof(char *) * (data->map.height + 1))
       SI data->map.grid es NULL -> RETORNAR ERROR

    2. Volcar los strings de la lista a la matriz:
       VARIABLE i = 0
       VARIABLE nodo_actual = data->map_list

       MIENTRAS nodo_actual NO SEA NULL:
           // Pasamos el string guardado en 'content' directamente al grid
           data->map.grid[i] = (char *)nodo_actual->content 
           nodo_actual = nodo_actual->next
           i++

       data->map.grid[i] = NULL // Cerrar la matriz con NULL

    3. Limpiar los nodos de la lista (¡pero NO el contenido!):
       MIENTRAS data->map_list NO SEA NULL:
           VARIABLE temporal = data->map_list
           data->map_list = data->map_list->next
           Liberar temporal // OJO: Haces free(temporal) pero NO free(temporal->content)

    RETORNAR (0) // Éxito. Ahora data->map.grid tiene todo tu mapa listo.

*/
int convert_list_to_array(t_data *data)
{
    int     i;
    t_list  *current_node;
    t_list  *tmp_node;
    
    // checks
    if (data->map_list == NULL || data->map.height == 0)
        return (print_error("Fichero sin mapa"));
    // resevo memeoria para grid
    data->map.grid = malloc((data->map.height + 1) * sizeof(char *));
    if (!data->map.grid)
        return (print_error("Malloc error en map.grid"));
    current_node = data->map_list;
    i = 0;
    while (current_node != NULL)
    {
        data->map.grid[i] = (char *)current_node->content;
        current_node = current_node->next;
        i++;
    }
    data->map.grid[i] = NULL;
    current_node = data->map_list;
    while (current_node != NULL)
    {
        tmp_node = current_node;
        current_node = current_node->next;
        free(tmp_node);
    }
    data->map_list = NULL;
    return (0);
}

/*
Siguiente Paso Técnico a tener en cuenta:
Fíjate en este detalle de tu parser_line:
if (line[i] == '\0' || line[i] == '\n')
{
    if (data->map_started == 1)
        print_error("Linea vacia dentro del mapa");
    return (0);
}

*/