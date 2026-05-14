
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

/*
    FUNCIÓN parser_main(archivo, data):
    1. ABRIR archivo (fd).
    2. SI error al abrir:
       RETORNAR print_error("No se pudo abrir el archivo").

    3. MIENTRAS (linea = get_next_line(fd)) no sea NULL:
       SI linea no es solo un salto de línea Y el mapa NO ha empezado:
          - Quitar espacios en blanco al principio y final de la linea (trim).

       RESULTADO = llamar a parse_line(linea, data).

       LIBERAR(linea).
       SI RESULTADO es ERROR:
          CERRAR(fd) y RETORNAR ERROR.

    4. CERRAR(fd).
    5. SI al terminar falta alguna textura o color:
       RETORNAR print_error("Información incompleta").

    RETORNAR SUCCESS.
*/
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
        print_error("No se pudo abrir el archivo");
        return (1);
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
    if (data->config_count < 6)
    {
        close(fd);
        print_error("Numero de texturas o colores incorrecto");
        return (1);
    }
    close(fd);
    return (0);
}

/*
    FUNCIÓN parse_line(linea, data):
    1. i = 0
    2. SALTAR espacios y tabuladores (while linea[i] == ' ' ...)

    3. SI linea[i] es el final ('\0' o '\n'):
       SI data->map_started == TRUE:
          RETORNAR print_error("Línea vacía dentro del mapa")
       RETORNAR SUCCESS

    4. get_texture() function
        SI empieza por "NO ", "SO ", "WE " o "EA ":
        if (ft_strncmp(&line[i], "NO ", 3) == 0)
            return (get_texture_path(&line[i], &data->tex_no, data));
       SI handle_texture(&linea[i], data) == SUCCESS:
          data->count_configs++  # <--- AQUÍ SUMAMOS
          RETORNAR SUCCESS
       SINO:
          RETORNAR ERROR

    5. get_color() function
        SI empieza por "F " o "C ":
       SI handle_color(&linea[i], data) == SUCCESS:
          data->count_configs++  # <--- AQUÍ SUMAMOS
          RETORNAR SUCCESS
       SINO:
          RETORNAR ERROR

    6. SI la línea parece mapa (contiene '1' o '0'):
       SI data->count_configs < 6:
          RETORNAR print_error("Mapa detectado antes de completar la configuración")

       data->map_started = TRUE
       RETORNAR save_map_line(linea, data) # Pasamos 'linea' original, no con 'i'

    7. RETORNAR print_error("Elemento desconocido en el archivo")
*/

int parser_line(char *line, t_data *data)
{
    int i;

    i = 0;
    while (line[i] == ' ' || (line[i] > 9 && line[i] < 13))
        i++;

    if (line[i] == '\0' || line[i] == '\n')
    {
        if (data->map_started == 1)
            print_error("Linea vacia dentro del mapa");
        return (0);
    }
    // intentar texturas
    if ((ft_strncmp(&line[i], "NO", 2) == 0 || ft_strncmp(&line[i], "SO", 2) == 0 || ft_strncmp(&line[i], "WE", 2) == 0 || ft_strncmp(&line[i], "EA", 2) == 0) && (line[i + 2] == ' ' || line[i + 2] == '\t'))
        return (handle_texture(&line[i], data));
    // intentar colors
    if ((line[i] == 'F' || line[i] == 'C') && (line[i + 1] == ' ' || line[i + 1] == '\t'))
        return (handle_color(&line[i], data));
    // es mapa?
    if (line[i] == '0' || line[i] == '1')
    {
        if (data->config_count < 6)
            return (print_error("Mapa detectado antes de completar la configuración"));
        return (0);
            //data->map_started = 1;
        //return (save_map_line(line, data)); // TODO!
    }
    return (print_error("Elemento desconocido en el archivo"));
}

