
#include "cub_3d.h"


/*
Check por mapas abiertos despues de flood_fill
*/

int is_open_floor(t_data *data, int row, int col)
{
	if (row == 0 || row == data->map.height - 1)
		return (1);
	if (col == 0 || col == data->map.width - 1)
		return (1);
	if (data->map.grid[row - 1][col] == ' ')
		return (1);
	if (data->map.grid[row][col - 1] == ' ')
		return(1);
	if (data->map.grid[row + 1][col] == ' ')
		return (1);
	if (data->map.grid[row][col + 1] == ' ')
		return (1);
	return (0);
}

int flood_fill(char **tmp_grid, int col, int row, t_data *data)
{
	// 1. Si el algoritmo se sale de los límites de la matriz -> El mapa está abierto (Error)
	if (row < 0 || row >= data->map.height || col < 0 || col >= data->map.width)
		return (1);    
	// 2. Si la inundación toca un espacio vacío o un fin de línea -> El mapa está abierto (Error)
	if (tmp_grid[row][col] == ' ' || tmp_grid[row][col] == '\0')
		return (1);
	// 3. Si toca un muro ('1') o una zona ya verificada ('V'), el camino está a salvo. Nos detenemos.
	if (tmp_grid[row][col] == '1' || tmp_grid[row][col] == 'V')
		return (0);
	// 4. Marcamos la celda actual como Visitada ('V') para no entrar en bucle infinito
	tmp_grid[row][col] = 'V';
	// 5. LLamamos recursivamente flood_fill arriba abajo y a los lados. Si cualquiera se escapa, devuelve 1.
	if (flood_fill(tmp_grid, col, row -1 , data)
		|| flood_fill(tmp_grid, col + 1, row, data)
		|| flood_fill(tmp_grid, col, row +1, data)
		|| flood_fill(tmp_grid, col - 1,row, data))
		return (1);
	return (0);
}
