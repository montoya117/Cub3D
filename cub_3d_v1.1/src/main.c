
#include "cub_3d.h"

void hardcodear_mapa(t_data *data)
{
    // Tamaño del mapa
    #define MAP_HEIGHT 5

    // Mapa de ejemplo: el jugador está en (2, 2) mirando al norte
    data->map.grid = malloc(sizeof(char *) * (MAP_HEIGHT + 1));
    if (!data->map.grid)
        return; // Maneja error si quieres

    data->map.grid[0] = ft_strdup("1111111111");
    data->map.grid[1] = ft_strdup("1000011001");
    data->map.grid[2] = ft_strdup("10N0001001");
    data->map.grid[3] = ft_strdup("1000000001");
    data->map.grid[4] = ft_strdup("1111111111");
    data->map.grid[5] = NULL;

    data->map.height = MAP_HEIGHT;
    data->map.width = 10; // todas las filas son iguales

    // Posición y dirección del jugador (coincide con la 'N' en [2][2])
    data->player.pos_x = 3;
    data->player.pos_y = 3;
    data->player.dir = 'N';
}

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
    //mientras no
    hardcodear_mapa(&data);
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
    mlx_key_hook(data.mlx.win_ptr, handle_keypress, &data);
    mlx_loop_hook(data.mlx.mlx_ptr, render, &data);
    mlx_loop(data.mlx.mlx_ptr);
    free_data(&data);
    return (0);
}