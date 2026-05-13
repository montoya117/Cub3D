
#include "cub_3d.h"

int main(int argc, char *argv[])
{
    t_data  data;
    char    *map_file;

    // checks...
    if (argc != 2)
    {
        print_error("Número de argumentos incorrectos");
        return (1);
    }
    map_file = argv[1];
    if  (!check_extension(map_file))
    {
        print_error("Extensión no válida");
        return (1);
    }
    // data_init
    init_data(&data);
    // parser
    if (parser_main(map_file, &data) != 0)
        return (1);
    printf("Let's go! Map i good!\n");
    return (0);
}