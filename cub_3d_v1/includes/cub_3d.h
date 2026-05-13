#ifndef CUB_3D_H
#define CUB_3D_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h> // printf
# include <unistd.h>
#include "../libft/includes/libft.h"
#include "../minilibx-mac/mlx.h"
//libft y minilibx 

// ** STRUCTS **

/* Map */
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
} t_map;

/* Player */
typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    char    dir; // 'N', 'S', 'O', 'E'     
} t_player;

/* Main data struct */
typedef struct s_data
{
    char        *tex_no; // textures
    char        *tex_so;
    char        *tex_we;
    char        *tex_ea;
    int         color_f;
    int         color_c;
    int         config_count;
    int         map_started; // map flag
    t_player    player;
    t_map       map;
} t_data;

// ** FUNCTIONS **s

// ** PARSER **

// ** INIT.C **
void    init_data(t_data *data);

// ** PARSER.C **
int     check_extension(char *str);
int     parser_main(char *map_file, t_data *data);
int     parser_line(char *line, t_data *data);

// ** UTILS **

int    print_error(char *str);

// ** GNL **
char	*get_next_line(int fd);

#endif