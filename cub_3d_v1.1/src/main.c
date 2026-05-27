
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
    //mientras no
    //hardcodear_mapa(&data);
    // parser
    if (parser_main(map_file, &data) != 0)
    {
        free_data(&data);
        return (1);
    }
    // validate 
    if (validate_elements_and_map(&data) != 0)
    {
        free_data(&data);
        return (1);
    }

    // -------------------------------------------------------------
    // ¡FUNCIÓN DE VALIDAR EL MAPA (Flood Fill, etc.)!
    // -------------------------------------------------------------

    // DEBUGG
    printf("\nLet's go! ¡Todo el archivo .cub es válido y seguro!\n");
    printf("--- CONFIG DATA ---\n");
    printf("NO: %s | SO: %s\n", data.tex_path_no, data.tex_path_so);
    printf("WE: %s | EA: %s\n", data.tex_path_we, data.tex_path_ea);
    printf("Floor: %d | Ceiling: %d\n", data.color_f, data.color_c);
    printf("Config count: %d/6\n", data.config_count);
    printf("-------------------\n");
    printf("--- PLAYER DATA ---\n");
    printf("Posición inicial centrada: (X: %f, Y: %f)\n", data.player.pos_x, data.player.pos_y);
    printf("Orientación original: %c\n", data.player.dir);
    printf("-------------------\n");
    printf("Mapa real limpio (Ancho máx: %d x Alto: %d):\n", data.map.width, data.map.height);

    // MAP DEBUG
    int y;
    if (data.map.grid)
    {
        y = 0;
        // Avanza solo mientras la línea exista. Si encuentra el NULL del final, se para de forma segura.
        while (data.map.grid[y] != NULL) 
        {
            printf("|%s|\n", data.map.grid[y]);
            y++;
        }
    }
    
    // init graphics
    if (!init_graphics(&data))
    {
        print_error("Error init. graphics.");
        free_data(&data);
        return (1);
    }
    /*
    if (load_textures(&data) != 0)
    {
        free_data(&data);
        return (1);
    }
    */
    mlx_hook(data.mlx.win_ptr, 2, 1L<<0, handle_keypress, &data);    // Key pressed
    mlx_hook(data.mlx.win_ptr, 3, 1L<<1, handle_keyrelease, &data);  // Key released
    mlx_loop_hook(data.mlx.mlx_ptr, render, &data);
    mlx_loop(data.mlx.mlx_ptr);
    
    free_data(&data);
    return (0);
}