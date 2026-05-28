
#include "cub_3d.h"
#include <math.h>

static	void	find_ray_hit(t_data *data, double ray_angle, double *dist)
{
	t_ray	r;

	r.dir_x = cos(ray_angle);
	r.dir_y = sin(ray_angle);
	r.ray_x = data->player.pos_x;
	r.ray_y = data->player.pos_y;
	*dist = 0.0;
	r.step = 0.01;
	r.hit = 0;
	while (!r.hit && *dist < 20.0)
	{
		r.ray_x += r.dir_x * r.step;
		r.ray_y += r.dir_y * r.step;
		*dist += r.step;
		r.map_x = (int)r.ray_x;
		r.map_y = (int)r.ray_y;
		if (r.map_y < 0 || r.map_y >= data->map.height
			|| r.map_x < 0
			|| r.map_x >= (int)ft_strlen(data->map.grid[r.map_y]))
			r.hit = 1;
		else if (data->map.grid[r.map_y][r.map_x] == '1')
			r.hit = 1;
	}
}

static void	draw_column(t_data *data, int x, double dir_angle)
{
	t_col	c;

	c.percent = (double)x / (double)WIN_W;
	c.ray_angle = dir_angle - (FOV / 2) + c.percent * FOV;
	find_ray_hit(data, c.ray_angle, &c.dist);
	c.dist = c.dist * cos(c.ray_angle - dir_angle);
	if (c.dist < 0.00001)
		c.dist = 0.00001;
	c.line_height = (int)(WIN_H / c.dist);
	c.y_start = WIN_H / 2 - c.line_height / 2;
	c.y_end = WIN_H / 2 + c.line_height / 2;
	c.y = c.y_start;
	while (c.y < c.y_end)
	{
		if (c.y >= 0 && c.y < WIN_H)
			buffer_put_pixel(&data->mlx, x, c.y, 0xCCCCCC);
		c.y++;
	}
}

void	draw(t_data *data)
{
	int		x;
	double	dir_angle;

	dir_angle = data->player.angle;
	x = 0;
	while (x < WIN_W)
	{
		draw_column(data, x, dir_angle);
		x++;
	}
	draw_minimap_buffer(data);
}

/*
structs ——>>

typedef struct s_ray
{
    // Vectores directores (los que sacas con cos y sin)
    double      dir_x;
    double      dir_y;

    // Posición actual en las casillas del mapa (matriz)
    int         map_x;
    int         map_y;

    // Las constantes fijas de la diagonal (el "precio" por casilla)
    double      delta_dist_x;
    double      delta_dist_y;

    // Los acumuladores (distancia al siguiente cruce de línea)
    double      side_dist_x;
    double      side_dist_y;

    // Dirección del salto en la matriz (siempre 1 o -1)
    int         step_x;
    int         step_y;

    // Flags de control de impacto
    int         hit;   // 0 si no hay muro, 1 si lo encuentra
    int         side;  // 0 si choca en cara vertical (X), 1 si choca en horizontal (Y)
    double      wall_x; // El porcentaje exacto (0.0 a 1.0) de impacto en el muro
}   t_ray;

typedef struct s_draw_data
{
    t_texture   *tex;
    int         tex_x;
    int         tex_y;
    double      step;
    double      tex_pos;
    int         color;
}   t_draw_data;

static void init_dda_vars(t_data *data, t_ray *r)
{
    // -------------------------------------------------------------
    // STEP 1: CALCULAR EL "PRECIO EN DIAGONAL" DE CADA EJE (DELTA)
    // -------------------------------------------------------------
    // ¿El rayo se mueve en horizontal?
    if (r->dir_x == 0)
    {
        r->delta_dist_x = 1e30; // Si va recto vertical, nunca cruza líneas en X (precio infinito)
    }
    else
    {
        r->delta_dist_x = fabs(1.0 / r->dir_x); // Hipotenusa para cruzar 1 bloque entero de X
    }

    // ¿El rayo se mueve en vertical?
    if (r->dir_y == 0)
    {
        r->delta_dist_y = 1e30; // Si va recto horizontal, nunca cruza líneas en Y (precio infinito)
    }
    else
    {
        r->delta_dist_y = fabs(1.0 / r->dir_y); // Hipotenusa para cruzar 1 bloque entero de Y
    }

    // -------------------------------------------------------------
    // STEP 2: LOCALIZAR LA BALDOSA INICIAL EN LA MATRIZ (ENTEROS)
    // -------------------------------------------------------------
    r->map_x = (int)data->player.pos_x; // Truncamos los decimales del jugador
    r->map_y = (int)data->player.pos_y; // Ejemplo: 3.45 se convierte en la casilla 3

    // -------------------------------------------------------------
    // STEP 3: CALCULAR EL PRIMER SALTO EN EL EJE X (HORIZONTALES)
    // -------------------------------------------------------------
    if (r->dir_x < 0)
    {
        r->step_x = -1; // El rayo va a la izquierda (restamos columnas en la matriz)
        
        // Distancia horizontal desde el jugador hasta la línea de ATRÁS,
        // multiplicada por el precio diagonal
        r->side_dist_x = (data->player.pos_x - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1; // El rayo va a la derecha (sumamos columnas en la matriz)
        
        // Distancia horizontal desde el jugador hasta la línea de DELANTE,
        // multiplicada por el precio diagonal
        r->side_dist_x = (r->map_x + 1.0 - data->player.pos_x) * r->delta_dist_x;
    }

    // -------------------------------------------------------------
    // STEP 4: CALCULAR EL PRIMER SALTO EN EL EJE Y (VERTICALES)
    // -------------------------------------------------------------
    if (r->dir_y < 0)
    {
        r->step_y = -1; // El rayo va hacia arriba (Norte, restamos filas en la matriz)
        
        // Distancia vertical desde el jugador hasta la línea de ARRIBA,
        // multiplicada por el precio diagonal
        r->side_dist_y = (data->player.pos_y - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1; // El rayo va hacia abajo (Sur, sumamos filas en la matriz)
        
        // Distancia vertical desde el jugador hasta la línea de ABAJO,
        // multiplicada por el precio diagonal
        r->side_dist_y = (r->map_y + 1.0 - data->player.pos_y) * r->delta_dist_y;
    }
}

static void find_ray_hit(t_data *data, t_ray *r)
{
    init_dda_vars(data, r);
    r->hit = 0;
    while (!r->hit)
    {
        if (r->side_dist_x < r->side_dist_y) // con k xocamos primero X o Y
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x; // avanze
            r->side = 0; // es horizontal 
        }
        else
        {
            r->side_dist_y += r->delta_dist_y;
            r->map_y += r->step_y; // avnze
            r->side = 1; // es vertical
        }
        if (r->map_y < 0 || r->map_y >= data->map.height
            || r->map_x < 0 || r->map_x >= data->map.width)
            break;
        if (data->map.grid[r->map_y][r->map_x] == '1')
            r->hit = 1;
    }
    // 1. Calculamos la posición exacta del impacto en el mundo 3D (Pitágoras puro)
    if (r->side == 0)
    {
        // Si chocó contra una pared vertical (Este/Oeste), queremos saber su altura Y
        r->wall_x = data->player.pos_y + (r->side_dist_x - r->delta_dist_x) * r->dir_y;
    }
    else
    {
        // Si chocó contra una pared horizontal (Norte/Sur), queremos saber su posición X
        r->wall_x = data->player.pos_x + (r->side_dist_y - r->delta_dist_y) * r->dir_x;
    }

    // 2. Nos quedamos SOLO con la parte decimal (el porcentaje dentro de la baldosa)
    r->wall_x = r->wall_x - floor(r->wall_x);
}

static t_texture *select_wall_texture(t_data *data, t_ray *r)
{
    if (r->side == 0)
    {
        if (r->dir_x > 0)
            return (&data->tex_img_ea);
        return (&data->tex_img_we);
    }
    if (r->dir_y > 0)
        return (&data->tex_img_so);
    return (&data->tex_img_no);
}

void draw_column(t_data *data, int x, double dir_angle)
{
    t_col       c;
    t_ray       r;
    t_draw_data d;

    // =========================================================================
    // 1. INICIALIZACIÓN DEL RAYO (ÁNGULO Y DIRECCIÓN)
    // =========================================================================
    // 'percent' nos dice en qué columna de la pantalla estamos (de 0.0 a 1.0)
    c.percent = (double)x / (double)WIN_W;
    
    // Calculamos el ángulo exacto de este rayo dentro de nuestro campo de visión (FOV)
    c.ray_angle = dir_angle - (FOV / 2.0) + c.percent * FOV;
    
    // Convertimos ese ángulo abstracto en vectores directores 2D usando cos y sin
    r.dir_x = cos(c.ray_angle);
    r.dir_y = sin(c.ray_angle);

    // =========================================================================
    // 2. EJECUCIÓN DE LA FÍSICA (DDA) Y DISTANCIA REAL
    // =========================================================================
    // Llamamos al DDA para que el rayo viaje por la matriz hasta chocar con un '1'
    find_ray_hit(data, &r);
    
    // TRADUCCIÓN DEL TERNARIO: Calculamos la distancia exacta perpendicular recorrida
    if (r.side == 0)
    {
        // Si chocó contra una pared vertical (Este/Oeste), usamos la distancia en X
        c.dist = r.side_dist_x - r.delta_dist_x;
    }
    else
    {
        // Si chocó contra una pared horizontal (Norte/Sur), usamos la distancia en Y
        c.dist = r.side_dist_y - r.delta_dist_y; // resto delta para k no sea pared
    }

    // =========================================================================
    // 3. PROYECCIÓN DE LA COLUMNA (CÁLCULO DEL TAMAÑO EN PANTALLA)
    // =========================================================================
    // Corrección del efecto "Ojo de Pez" (multiplicamos por el coseno del ángulo relativo)
    c.dist = c.dist * cos(c.ray_angle - dir_angle);
    
    // Protección anti-cracheo: Si estamos pegados al muro, la distancia no puede ser 0
    if (c.dist < 0.00001)
        c.dist = 0.00001;
        
    // Calculamos el alto del muro en la pantalla (A menos distancia, más alto el muro)
    c.line_height = (int)(WIN_H / c.dist);
    
    // Calculamos el píxel de arriba (y_start) y el de abajo (y_end) donde empieza el muro
    c.y_start = WIN_H / 2 - c.line_height / 2;
    c.y_end = WIN_H / 2 + c.line_height / 2;

    // =========================================================================
    // 4. CONFIGURACIÓN DEL MAPEO DE TEXTURAS (DÓNDE GOLPEA EN EL XPM)
    // =========================================================================
    // Seleccionamos la textura correcta (NO, SO, EA, WE) basándonos en 'side' y la dirección
    d.tex = select_wall_texture(data, &r);
    
    // Pasamos el porcentaje del muro (wall_x) a píxeles reales de ancho de la textura
    d.tex_x = (int)(r.wall_x * (double)d.tex->width);
    
    // Si vemos la pared al revés (espejo), invertimos el eje X de la textura para que no se lea volteada
    if ((r.side == 0 && r.dir_x > 0) || (r.side == 1 && r.dir_y < 0))
        d.tex_x = d.tex->width - d.tex_x - 1;
        
    // 'step' nos dice cuántos píxeles de la textura avanzar por cada píxel de pantalla
    d.step = (double)d.tex->height / (double)c.line_height;
    
    // Calculamos la posición inicial de textura, adaptada por si el muro es más alto que la pantalla
    d.tex_pos = (c.y_start - WIN_H / 2 + c.line_height / 2) * d.step;

    // 5. Ajuste y Renderizado Vertical
    render_ray(data, x, &c, &r, &d);
}

static void render_ray(t_data *data, int x, t_col *c, t_ray *r, t_draw_data *d)
{
    // 1. Ajuste del límite superior (Si el muro se sale por arriba)
    c->y = c->y_start;
    if (c->y < 0)
    {
        d->tex_pos += d->step * (-c->y);
        c->y = 0;
    }
    
    // 2. Ajuste del límite inferior (Si el muro se sale por abajo)
    if (c->y_end > WIN_H)
        c->y_end = WIN_H;
        
    // 3. El bucle vertical de pintado píxel a píxel
    while (c->y < c->y_end)
    {
        // Calculamos la fila exacta de la textura (con el truco binario anti-SegFault)
        d->tex_y = (int)d->tex_pos & (d->tex->height - 1);
        
        // Extraemos el color del archivo XPM
        d->color = get_texture_pixel(d->tex, d->tex_x, d->tex_y);
        
        // Si es cara Norte/Sur, aplicamos la sombra longitudinal
        if (r->side == 1)
            d->color = (d->color >> 1) & 0x7F7F7F;
            
        // Pintamos el píxel en el buffer de la MLX
        buffer_put_pixel(&data->mlx, x, c->y, d->color);
        
        // Avanzamos en la textura y bajamos un píxel en la pantalla
        d->tex_pos += d->step;
        c->y++;
    }
}

void draw_column(t_data *data, int x, double dir_angle)
{
    t_col       c;
    t_ray       r;
    t_draw_data d;

    // 1. Inicialización del Rayo
    c.percent = (double)x / (double)WIN_W;
    c.ray_angle = dir_angle - (FOV / 2.0) + c.percent * FOV;
    r.dir_x = cos(c.ray_angle);
    r.dir_y = sin(c.ray_angle);

    // 2. Ejecución de la Física (DDA)
    find_ray_hit(data, &r);
    c.dist = (r.side == 0) ? (r.side_dist_x - r.delta_dist_x) : (r.side_dist_y - r.delta_dist_y);

    // 3. Proyección de la Columna (Pantalla)
    c.dist = c.dist * cos(c.ray_angle - dir_angle);
    if (c.dist < 0.00001)
        c.dist = 0.00001;
    c.line_height = (int)(WIN_H / c.dist);
    c.y_start = WIN_H / 2 - c.line_height / 2;
    c.y_end = WIN_H / 2 + c.line_height / 2;

    // 4. Configuración del Mapeo de Texturas
    d.tex = select_wall_texture(data, &r);
    d.tex_x = (int)(r.wall_x * (double)d.tex->width);
    if ((r.side == 0 && r.dir_x > 0) || (r.side == 1 && r.dir_y < 0))
        d.tex_x = d.tex->width - d.tex_x - 1;
    d.step = (double)d.tex->height / (double)c.line_height;
    d.tex_pos = (c.y_start - WIN_H / 2 + c.line_height / 2) * d.step;

    // 5. Ajuste y Renderizado Vertical
    c.y = c.y_start;
    if (c.y < 0)
    {
        d.tex_pos += d.step * (-c.y);
        c.y = 0;
    }
    if (c.y_end > WIN_H)
        c.y_end = WIN_H;
    while (c.y < c.y_end)
    {
        d.tex_y = (int)d.tex_pos & (d.tex->height - 1);
        d.color = get_texture_pixel(d.tex, d.tex_x, d.tex_y);
        if (r.side == 1)
            d.color = (d.color >> 1) & 0x7F7F7F;
        buffer_put_pixel(&data->mlx, x, c.y, d.color);
        d.tex_pos += d.step;
        c.y++;
    }
}

*/


/* 
final version right order --------------->>>>
// ... (Tus structs s_ray y s_draw_data e init_dda_vars se quedan igual arriba)

static void init_dda_vars(t_data *data, t_ray *r)
{
    // -------------------------------------------------------------
    // STEP 1: CALCULAR EL "PRECIO EN DIAGONAL" DE CADA EJE (DELTA)
    // -------------------------------------------------------------
    // ¿El rayo se mueve en horizontal?
    if (r->dir_x == 0)
    {
        r->delta_dist_x = 1e30; // Si va recto vertical, nunca cruza líneas en X (precio infinito)
    }
    else
    {
        r->delta_dist_x = fabs(1.0 / r->dir_x); // Hipotenusa para cruzar 1 bloque entero de X
    }

    // ¿El rayo se mueve en vertical?
    if (r->dir_y == 0)
    {
        r->delta_dist_y = 1e30; // Si va recto horizontal, nunca cruza líneas en Y (precio infinito)
    }
    else
    {
        r->delta_dist_y = fabs(1.0 / r->dir_y); // Hipotenusa para cruzar 1 bloque entero de Y
    }

    // -------------------------------------------------------------
    // STEP 2: LOCALIZAR LA BALDOSA INICIAL EN LA MATRIZ (ENTEROS)
    // -------------------------------------------------------------
    r->map_x = (int)data->player.pos_x; // Truncamos los decimales del jugador
    r->map_y = (int)data->player.pos_y; // Ejemplo: 3.45 se convierte en la casilla 3

    // -------------------------------------------------------------
    // STEP 3: CALCULAR EL PRIMER SALTO EN EL EJE X (HORIZONTALES)
    // -------------------------------------------------------------
    if (r->dir_x < 0)
    {
        r->step_x = -1; // El rayo va a la izquierda (restamos columnas en la matriz)
        
        // Distancia horizontal desde el jugador hasta la línea de ATRÁS,
        // multiplicada por el precio diagonal
        r->side_dist_x = (data->player.pos_x - r->map_x) * r->delta_dist_x;
    }
    else
    {
        r->step_x = 1; // El rayo va a la derecha (sumamos columnas en la matriz)
        
        // Distancia horizontal desde el jugador hasta la línea de DELANTE,
        // multiplicada por el precio diagonal
        r->side_dist_x = (r->map_x + 1.0 - data->player.pos_x) * r->delta_dist_x;
    }

    // -------------------------------------------------------------
    // STEP 4: CALCULAR EL PRIMER SALTO EN EL EJE Y (VERTICALES)
    // -------------------------------------------------------------
    if (r->dir_y < 0)
    {
        r->step_y = -1; // El rayo va hacia arriba (Norte, restamos filas en la matriz)
        
        // Distancia vertical desde el jugador hasta la línea de ARRIBA,
        // multiplicada por el precio diagonal
        r->side_dist_y = (data->player.pos_y - r->map_y) * r->delta_dist_y;
    }
    else
    {
        r->step_y = 1; // El rayo va hacia abajo (Sur, sumamos filas en la matriz)
        
        // Distancia vertical desde el jugador hasta la línea de ABAJO,
        // multiplicada por el precio diagonal
        r->side_dist_y = (r->map_y + 1.0 - data->player.pos_y) * r->delta_dist_y;
    }
}


static void find_ray_hit(t_data *data, t_ray *r)
{
    init_dda_vars(data, r);
    r->hit = 0;
    while (!r->hit)
    {
        if (r->side_dist_x < r->side_dist_y) // ¿Con qué chocamos primero, línea X o Y?
        {
            r->side_dist_x += r->delta_dist_x;
            r->map_x += r->step_x; // Avance en columnas
            r->side = 0;           // Impacto en pared vertical (Este/Oeste)
        }
        else
        {
            r->side_dist_y += r->delta_dist_y;
            r->map_y += r->step_y; // Avance en filas
            r->side = 1;           // Impacto en pared horizontal (Norte/Sur)
        }
        if (r->map_y < 0 || r->map_y >= data->map.height
            || r->map_x < 0 || r->map_x >= data->map.width)
            break;
        if (data->map.grid[r->map_y][r->map_x] == '1')
            r->hit = 1;
    }
    // 1. Calculamos la posición exacta del impacto en el mundo 3D (Pitágoras puro)
    if (r->side == 0)
        r->wall_x = data->player.pos_y + (r->side_dist_x - r->delta_dist_x) * r->dir_y;
    else
        r->wall_x = data->player.pos_x + (r->side_dist_y - r->delta_dist_y) * r->dir_x;

    // 2. Nos quedamos SOLO con la parte decimal (el porcentaje dentro de la baldosa)
    r->wall_x = r->wall_x - floor(r->wall_x);
}

static t_texture *select_wall_texture(t_data *data, t_ray *r)
{
    if (r->side == 0)
    {
        if (r->dir_x > 0)
            return (&data->tex_img_ea);
        return (&data->tex_img_we);
    }
    if (r->dir_y > 0)
        return (&data->tex_img_so);
    return (&data->tex_img_no);
}

// CAMBIO DE ORDEN: Ponemos render_ray AQUÍ para que draw_column la conozca al compilar
static void render_ray(t_data *data, int x, t_col *c, t_ray *r, t_draw_data *d)
{
    // 1. Ajuste del límite superior (Si el muro se sale por arriba de la pantalla)
    c->y = c->y_start;
    if (c->y < 0)
    {
        d->tex_pos += d->step * (-c->y);
        c->y = 0;
    }
    
    // 2. Ajuste del límite inferior (Si el muro se sale por abajo de la pantalla)
    if (c->y_end > WIN_H)
        c->y_end = WIN_H;
        
    // 3. El bucle vertical de pintado píxel a píxel
    while (c->y < c->y_end)
    {
        // Calculamos la fila exacta de la textura (con el truco binario anti-SegFault)
        d->tex_y = (int)d->tex_pos & (d->tex->height - 1);
        
        // Extraemos el color del archivo XPM
        d->color = get_texture_pixel(d->tex, d->tex_x, d->tex_y);
        
        // Si es cara Norte/Sur (side == 1), aplicamos la sombra longitudinal
        if (r->side == 1)
            d->color = (d->color >> 1) & 0x7F7F7F;
            
        // Pintamos el píxel en el buffer de la MLX
        buffer_put_pixel(&data->mlx, x, c->y, d->color);
        
        // Avanzamos en la textura y bajamos un píxel en la pantalla
        d->tex_pos += d->step;
        c->y++;
    }
}

void draw_column(t_data *data, int x, double dir_angle)
{
    t_col       c;
    t_ray       r;
    t_draw_data d;

    // 1. INICIALIZACIÓN DEL RAYO (ÁNGULO Y DIRECCIÓN)
    c.percent = (double)x / (double)WIN_W;
    c.ray_angle = dir_angle - (FOV / 2.0) + c.percent * FOV;
    r.dir_x = cos(c.ray_angle);
    r.dir_y = sin(c.ray_angle);

    // 2. EJECUCIÓN DE LA FÍSICA (DDA) Y DISTANCIA REAL
    find_ray_hit(data, &r);
    if (r.side == 0)
        c.dist = r.side_dist_x - r.delta_dist_x;
    else
        c.dist = r.side_dist_y - r.delta_dist_y; // Resto delta para volver a la cara del muro

    // 3. PROYECCIÓN DE LA COLUMNA (CÁLCULO DEL TAMAÑO EN PANTALLA)
    c.dist = c.dist * cos(c.ray_angle - dir_angle);
    if (c.dist < 0.00001)
        c.dist = 0.00001;
    c.line_height = (int)(WIN_H / c.dist);
    c.y_start = WIN_H / 2 - c.line_height / 2;
    c.y_end = WIN_H / 2 + c.line_height / 2;

    // 4. CONFIGURACIÓN DEL MAPEO DE TEXTURAS
    d.tex = select_wall_texture(data, &r);
    d.tex_x = (int)(r.wall_x * (double)d.tex->width);
    if ((r.side == 0 && r.dir_x > 0) || (r.side == 1 && r.dir_y < 0))
        d.tex_x = d.tex->width - d.tex_x - 1;
    d.step = (double)d.tex->height / (double)c.line_height;
    d.tex_pos = (c.y_start - WIN_H / 2 + c.line_height / 2) * d.step;

    // 5. Ajuste y Renderizado Vertical (Llamada limpia)
    render_ray(data, x, &c, &r, &d);
}
*/