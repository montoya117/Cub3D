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

#ifndef M_SPRITE_FRAMES
# define SPRITE_FRAMES 3
#endif

// Macros for KEYs
#ifdef __APPLE__
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
#else
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
#endif

#include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h> // printf
# include <unistd.h>
# include <string.h> 
# include <errno.h>
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


//STRUCTS AUXILIARES PARA DIBUJAR
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	ray_x;
	double	ray_y;
	double	step;
	int		map_x;
	int		map_y;
	int		hit;
}	t_ray;

typedef struct s_col
{
	double	percent;
	double	ray_angle;
	double	dist;
	int		line_height;
	int		y_start;
	int		y_end;
	int		y;
}	t_col;

//struc animacion
typedef struct s_anim {
    int sprite_w;
int sprite_h;
    int active;      
    int frame;       
    double x, y;   
    int delay;       // Ticks a mostrar cada frame
    int tick;        // Contador para cambiar de frame
} t_anim;

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
    int         key_w;
    int         key_a;
    int         key_s;
    int         key_d;
    int         key_left;
    int         key_right;
    void        *sprite_textures[SPRITE_FRAMES];
    int sprite_w;
    int sprite_h;
    t_anim      explosion;
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
int     check_all_floors_closed(t_data *data);
int     validate_elements_and_map(t_data *data);

// ** VALIDATE_HELPERS.C **
int     is_open_floor(t_data *data, int row, int col);
int     flood_fill(char **tmp_grid, int col, int row, t_data *data);

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
int handle_keyrelease(int keycode, t_data *data);

//MOVE
int is_wall(double x, double y, t_data *data);
int can_move(double new_x, double new_y, t_data *data);
void check_and_move(double new_x, double new_y, t_data *data);
void rotate_player(int keycode, t_data *data);
void move_player(int keycode, t_data *data);


//PROCESS_MOVEMENT.C
void process_movement(t_data *data);

//SPRITES
void	draw_explosion_in_buffer(t_data *data);
void update_explosion_anim(t_data *data);

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