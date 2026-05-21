#ifndef CUB_3D_H
#define CUB_3D_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#ifndef WIN_W
# define WIN_W 1024 
#endif

#ifndef WIN_H
# define WIN_H 768  
#endif

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
# define M_PI_2 1.5707963267948966
#endif

#include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h> // printf
# include <unistd.h>
# include <math.h>
#include "../libft/includes/libft.h"
#include "../minilibx/mlx.h" 
//libft y minilibx 

// ** STRUCTS **

/*MLX STRUCT*/
typedef struct s_mlx
{
    void    *mlx_ptr;   // Contexto minlbx
    void    *win_ptr;   // Ventana principal
    void    *img_ptr;   // Imagen para el render principal
    char    *img_data;  // Datos de pixeles de la imagen (devueltos x mlx_get_data_addr)
    int     bpp;
    int     size_line;
    int     endian;
} t_mlx;

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
    double  angle;
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
    t_list      *map_list; //map antes de pasar a grid !!NUEVO
    t_player    player;
    t_map       map;
    t_mlx       mlx;
} t_data;

typedef struct s_map_node
{
    char                *line;
    struct s_map_node   *next;    
}   t_map_node;

// ** FUNCTIONS **s

// ** PARSER **

// ** INIT.C **
void    init_data(t_data *data);

// ** PARSER.C **
int     check_extension(char *str);
int     parser_main(char *map_file, t_data *data);
int     parser_line(char *line, t_data *data);

// ** PARSE_CONF_TEXTURES.C **
int     handle_texture(char *line, t_data *data);

// ** PARSE_CONF_COLORS.C **
int     handle_color(char *line, t_data *data);
int     validate_rgb(char **rgb, int *target);

// ** PARSE_MAP.C **
int     is_map_line(char *line);
int     save_map_line(char *valid_line, t_data *data);
int     convert_list_to_array(t_data *data);

// ** VALIDATE.C **
int     check_elements(t_data *data);
int     check_player(t_data *data);
int     check_walls(t_data *data);
int     flood_fill(char **tmp_grid, int col, int row, t_data *data);
int     validate_elements_and_map(t_data *data);


// ** UTILS **
// ** UTILS_PARSER.C **
int     is_str_digit(char *str);

// ** UTILS_VALIDATEC **
void    free_matrix(char **matrix, int  height);
char	**duplicate_matrix(char **src_matrix, int height);

//INIT_GRAPHICS.C
int init_graphics(t_data *data);

//HOOKS
int	handle_keypress(int keycode, t_data *data);

//MOVE
int is_wall(double x, double y, t_data *data);
int can_move(double new_x, double new_y, t_data *data);
void check_and_move(double new_x, double new_y, t_data *data);
void rotate_player(int keycode, t_data *data);
void move_player(int keycode, t_data *data);

//RENDER.C
int render(t_data *data);
//DRAW.c
void draw(t_data *data);
//BUFFER_UTILS.C
void buffer_put_pixel(t_mlx *mlx, int x, int y, int color);
void clear_img_buffer(t_mlx *mlx);
//DRAW_MINIMAP.C
void draw_minimap_buffer(t_data *data);

// ** ERROR.C **
int     print_error(char *str);
void    free_array(char **array);
void	free_data(t_data *data);
void    free_map_list(t_list *map_list);

// ** GNL **
char	*get_next_line(int fd);

#endif