
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

    
    // DEBUGG
    printf("Let's go! Config is good!\n");
    printf("--- DEBUG DATA ---\n");
    printf("NO: %s | SO: %s\n", data.tex_no, data.tex_so);
    printf("WE: %s | EA: %s\n", data.tex_we, data.tex_ea);
    printf("Floor: %d | Ceiling: %d\n", data.color_f, data.color_c);
    printf("Config count: %d/6\n", data.config_count);
    printf("------------------\n");
    printf("Mapa: %d x %d\n", data.map.width, data.map.height);
    for (int y = 0; y < data.map.height; y++)
    printf("|%s|\n", data.map.grid[y]);
    printf("Player en (%f, %f)\n", data.player.pos_x, data.player.pos_y);


    // init graphics
    if (!init_graphics(&data))
    {
        print_error("Error init. graphics.");
        free_data(&data);
        return (1);
    }
    mlx_loop_hook(data.mlx.mlx_ptr, render, &data);
    mlx_loop(data.mlx.mlx_ptr);
    free_data(&data);
    return (0);
}