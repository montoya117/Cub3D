
#include "cub_3d.h"

/*
    - is_map_line: Detecta si la línea contiene solo 01NSEW y espacios.
    - save_map_line: Guarda la línea temporalmente (en una lista o un string acumulado).
    - convert_list_to_array: Transforma lo guardado en el char **grid final.
*/

/*
    Opción A: La Lista Enlazada (Estructurada y Limpia)
    Es la más segura para no tener que estar haciendo malloc y free constantemente mientras unes strings.

    FUNCIÓN save_map_line(linea, data):
    1. Crear un NUEVO NODO para una lista enlazada.
    2. Guardar en el nodo el contenido de 'linea' (usando ft_strdup).
    3. Añadir el nodo al FINAL de la lista que tenemos en data->map_list.
    4. Incrementar data->map.height (así ya sabemos cuántas filas hay).

    Al terminar el bucle de GNL:
    FUNCIÓN convert_list_to_grid(data):
    1. Hacer MALLOC de data->map.grid usando (height + 1).
    2. Recorrer la lista enlazada nodo a nodo.
    3. Copiar el string de cada nodo en una posición del grid: grid[i] = nodo->content.
    4. Poner NULL en la última posición: grid[height] = NULL.
    5. Liberar todos los nodos de la lista (pero NO los strings, que ahora están en el grid).
*/

/*
    Opción B: El Super-String (Rápida y basada en Libft)
    Esta aprovecha que ya tienes un ft_split y un ft_strjoin en tu librería.

    FUNCIÓN save_map_line(linea, data):
    1. Crear un SEPARADOR único (ejemplo: un carácter que no esté en el mapa, como '\v').
    2. Usar un strjoin especial (join_and_free):
       data->map_string = strjoin(data->map_string, linea);
       data->map_string = strjoin(data->map_string, SEPARADOR);
    3. (Importante liberar el string viejo en cada join para no tener leaks).

    Al terminar el bucle de GNL:
    FUNCIÓN convert_string_to_grid(data):
    1. data->map.grid = ft_split(data->map_string, SEPARADOR);
    2. Contar cuántos elementos tiene el grid para sacar data->map.height.
    3. Liberar data->map_string.
*/