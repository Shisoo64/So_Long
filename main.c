#include "so_long.h"

typedef struct	s_sprites {
	void	*floor;
	void	*wall;
	void	*collec;
	void	*player;
	void	*exit;
}				t_sprites;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	char	**map;
	int	collec;
	t_sprites	sprites;
}				t_vars;

static int	exit_hook(void)
{
	//free all
	exit(0);
}

int	move_player(int diry, int dirx, t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while(vars->map[++y])
	{
		x = -1;
		while(vars->map[y][++x])
		{
			if(vars->map[y][x] == 'P' && (vars->map[y + diry][x + dirx] == '0' || vars->map[y + diry][x + dirx] == 'C'))
			{
				if(vars->map[y + diry][x + dirx] == 'C')
					vars->collec--;
				vars->map[y][x] = '0';
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.floor, IMG_SIZE * x, IMG_SIZE * y);
				vars->map[y + diry][x + dirx] = 'P';
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.player, IMG_SIZE * (x + dirx), IMG_SIZE * (y + diry));
				return(1);
			}
			if(vars->map[y][x] == 'P' && vars->map[y + diry][x + dirx] == 'E' && vars->collec == 0)
				exit(0);
		}
	}
	return(0);
}

void	cycle(int key, t_vars *vars)
{
	if(key == KEY_UP)
		move_player(1, 0, vars);
	else if(key == KEY_LEFT)
		move_player(0, -1, vars);
	else if(key == KEY_DOWN)
		move_player(-1, 0, vars);
	else if(key == KEY_RIGHT)
		move_player(0, 1, vars);
	else
		return;
}

int	inputs(int key, t_vars *vars)
{
	if (key == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else
		cycle(key, vars);
	return (0);
}

int	get_map_height()
{
	int	fd;
	int	i;
	char	*line;

	i = 1;
	fd = open("./map.ber",0);
	line = get_next_line(fd);
	while(line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

char	**create_map()
{
	char	**map;
	int	fd;
	int	map_height;
	int	i;

	i = 0;
	map_height = get_map_height();
	fd = open("./map.ber",0);
	map = malloc(sizeof(char*) * map_height);
	map[0] = get_next_line(fd);
	while(++i < map_height)
		map[i] = get_next_line(fd);
	close(fd);
	return (map);
}

t_sprites	get_sprites(t_vars vars)
{
	t_sprites sprites;
	char	*floor_path = "./sprites/floor.xpm";
	char	*wall_path = "./sprites/wall.xpm";
	char	*collec_path = "./sprites/collec.xpm";
	char	*player_path = "./sprites/player.xpm";
	char	*exit_path = "./sprites/exit.xpm";
	int	img_width;
	int	img_height;

	sprites.floor = mlx_xpm_file_to_image(vars.mlx, floor_path, &img_width, &img_height);
	sprites.wall = mlx_xpm_file_to_image(vars.mlx, wall_path, &img_width, &img_height);
	sprites.collec = mlx_xpm_file_to_image(vars.mlx, collec_path, &img_width, &img_height);
	sprites.player = mlx_xpm_file_to_image(vars.mlx, player_path, &img_width, &img_height);
	sprites.exit = mlx_xpm_file_to_image(vars.mlx, exit_path, &img_width, &img_height);
	return (sprites);
}

void	print_map(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while(vars->map[++y])
	{
		x = -1;
		while(vars->map[y][++x])
		{
			if(vars->map[y][x] == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.floor, IMG_SIZE * x, IMG_SIZE * y);
			if(vars->map[y][x] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall, IMG_SIZE * x, IMG_SIZE * y);
			if(vars->map[y][x] == 'P')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.player, IMG_SIZE * x, IMG_SIZE * y);
			if(vars->map[y][x] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.exit, IMG_SIZE * x, IMG_SIZE * y);
			if(vars->map[y][x] == 'C')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.collec, IMG_SIZE * x, IMG_SIZE * y);
				vars->collec++;
			}
		}
	}
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.collec = 0;
	vars.sprites = get_sprites(vars);
	vars.map = create_map();
	vars.win = mlx_new_window(vars.mlx, IMG_SIZE * 64, IMG_SIZE * 64, "Super Romil!");
	mlx_key_hook(vars.win, inputs, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	print_map(&vars);

	mlx_loop(vars.mlx);
}
