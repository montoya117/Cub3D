
#include "cub_3d.h"

static int	handle_args(int argc, char **argv, char **map_file)
{
	if (argc != 2)
		return (print_error("Número de argumentos incorrectos"), 1);
	*map_file = argv[1];
	if (!check_extension(*map_file))
		return (print_error("Extensión no válida"), 1);
	return (0);
}

static int	handle_parsing_and_validation(char *map_file, t_data *data)
{
	init_data(data);
	if (parser_main(map_file, data) != 0)
		return (free_data(data), 1);
	if (validate_elements_and_map(data) != 0)
		return (free_data(data), 1);
	return (0);
}

static int	start_graphics(t_data *data)
{
	if (!init_graphics(data))
		return (print_error("Error init. graphics."), free_data(data), 1);
	if (load_textures(data) != 0)
		return (free_data(data), 1);
	return (0);
}

static void	setup_mlx_hooks(t_data *data)
{
	mlx_hook(data->mlx.win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->mlx.win_ptr, 3, 1L << 1, handle_keyrelease, data);
	mlx_hook(data->mlx.win_ptr, 17, 0, close_program, data);
	mlx_loop_hook(data->mlx.mlx_ptr, render, data);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	char	*map_file;

	if (handle_args(argc, argv, &map_file))
		return (1);
	if (handle_parsing_and_validation(map_file, &data))
		return (1);
	if (start_graphics(&data))
		return (1);
	setup_mlx_hooks(&data);
	mlx_loop(data.mlx.mlx_ptr);
	free_data(&data);
	return (0);
}

/*
int main(int argc, char *argv[])
{
	t_data	data;
	char	*map_file;
	int		y;

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
	init_data(&data);
	if (parser_main(map_file, &data) != 0)
	{
		free_data(&data);
		return (1);
	}
	if (validate_elements_and_map(&data) != 0)
	{
		free_data(&data);
		return (1);
	}
	if (data.map.grid)
	{
		y = 0;
		while (data.map.grid[y] != NULL)
		{
			printf("|%s|\n", data.map.grid[y]);
			y++;
		}
	}
	if (!init_graphics(&data))
	{
		print_error("Error init. graphics.");
		free_data(&data);
		return (1);
	}
	if (load_textures(&data) != 0)
	{
		free_data(&data);
		return (1);
	}
	mlx_hook(data.mlx.win_ptr, 2, 1L<<0, handle_keypress, &data);
	mlx_hook(data.mlx.win_ptr, 3, 1L<<1, handle_keyrelease, &data);
	mlx_hook(data.mlx.win_ptr, 17, 0, close_program, &data);
	mlx_loop_hook(data.mlx.mlx_ptr, render, &data);
	mlx_loop(data.mlx.mlx_ptr);
	free_data(&data);
	return (0);
}
*/