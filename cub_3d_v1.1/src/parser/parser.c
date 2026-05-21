
#include "cub_3d.h"

/*
El archivo .cub (Ejemplo de Input)

NO ./textures/norte.xpm
SO ./textures/sur.xpm
WE ./textures/oeste.xpm
EA ./textures/este.xpm

F 220,100,0
C 225,30,0

        11111111111
        10000000001
        10110000011
        1011011101
11111111101101110111
10000000000000000001
10000000000000000001
11111111111111111111

parser_main()
   │
   ├── [Lectura con GNL y save_map_line]
   │
   ├── convert_list_to_array()  <-- Creamos la matriz char **grid
   │
   └── validate_map_data()      <-- Tu función principal de validación
          │
          ├── check_elements()  <-- ¿Están las 4 texturas y 2 colores?
          │
          ├── check_player()    <-- ¿Hay un solo jugador? (Y guardas su posición)
          │
          └── check_walls()     <-- Aquí empieza la magia de los muros
                 │
                 └── flood_fill()  <-- El algoritmo recursivo busca fugas

*/

/*
    - check_extension: Valida que el archivo sea .cub.
    - parser_main: El bucle que lee con get_next_line y decide qué hacer.
    - parse_line: El "router" que identifica si la línea es configuración, mapa o basura.
*/

// devuelve 1 si es valida 0 si no
int check_extension(char *str)
{
    int len;

    if (!str)
        return (0);
    len = ft_strlen(str);
    if (len < 5)
        return (0);
    if (ft_strncmp(&str[len - 4], ".cub", 4) == 0)
        return (1);
    return (0);
}

// parser_main hace el open y un while con readline

int parser_main(char *map_file, t_data *data)
{
    char *line;
    int fd;
    int len;

    line = NULL;
    fd = -1;
    fd = open(map_file, O_RDONLY);
    if (fd == -1)
    {
        // ! MIRAR Poblemas de open! mirar man '
        // TODO
        return (print_error("No se pudo abrir el archivo"));
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        // cambiamos /n por '\0'
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len -1] = '\0';
        if (parser_line(line, data) != 0)
        {
            free(line);
            close(fd);
            return (1);
        }
        free(line);
    }
    close(fd);
    if (data->config_count < 6)
        return (print_error("Numero de texturas o colores incorrecto"));
    if (convert_list_to_array(data) != 0)
        return (1); 
    return (0);
}

// parser_line decide si es textura, color o mapa

int parser_line(char *line, t_data *data)
{
    int i;

    i = 0;
    while (line[i] == ' ' || (line[i] > 9 && line[i] < 13))
        i++;

    if (line[i] == '\0' || line[i] == '\n')
    {
        if (data->map_started == 1)
            return (print_error("Linea vacia dentro del mapa"));
        return (0);
    }
    // intentar texturas
    if ((ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0 || ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA", 2) == 0) && (line[i + 2] == ' ' || line[i + 2] == '\t'))
        return (handle_texture(&line[i], data));
    // intentar colors
    if ((line[i] == 'F' || line[i] == 'C') && (line[i + 1] == ' ' || line[i + 1] == '\t'))
        return (handle_color(&line[i], data));
    // es mapa?
    if (is_map_line(line))
    {
        if (data->config_count < 6)
            return (print_error("Mapa detectado antes de completar la configuración"));
        return (save_map_line(line, data));
    }
    return (print_error("Elemento desconocido en el archivo"));
}

