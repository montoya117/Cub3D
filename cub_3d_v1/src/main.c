
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
    {
        free_data(&data);
        return (1);
    }
    printf("Let's go! Config is good!\n");
    printf("--- DEBUG DATA ---\n");
    printf("NO: %s | SO: %s\n", data.tex_no, data.tex_so);
    printf("WE: %s | EA: %s\n", data.tex_we, data.tex_ea);
    printf("Floor: %d | Ceiling: %d\n", data.color_f, data.color_c);
    printf("Config count: %d/6\n", data.config_count);
    printf("------------------\n");

    free_data(&data);
    return (0);
}