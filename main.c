#include "so_long.h"

typedef struct	s_sprites {
	void	*floor;
	void	*collec[COLLEC_FRAMES + 1];
	void	*playerup;
	void	*playerdown;
	void	*playerleft;
	void	*playerright;
	void	*exit[2];
	void	*wall;
	void	*wall_down;
	void	*wall_downleft;
	void	*wall_downright;
	void	*wall_left;
	void	*wall_right;
	void	*wall_upleft;
	void	*wall_upright;
	void	*wall_up;

}				t_sprites;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	char	**map;
	char	*mapname;
	int	map_y;
	int	map_x;
	int	collec;
	int	moves;
	int	timer;
	t_sprites	sprites;
}				t_vars;

int	ft_strlen_n(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i++])
		;
	return (--i);
}


void	ft_count(int n, int i[2])
{
	int	x;

	i[0] = 1;
	i[1] = 0;
	if (n < 0)
		i[1]++;
	x = n;
	while (x >= 10 || x <= -10)
	{
		x /= 10;
		i[0]++;
	}
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		i[2];

	ft_count(n, i);
	if (i[1])
		n = -n;
	tab = malloc(sizeof(char) * ((i[0] += i[1]) + 1));
	if (!tab)
		return (NULL);
	tab[i[0]] = '\0';
	while (i[0]--)
	{
		tab[i[0]] = (n % 10) + '0';
		n /= 10;
	}
	if (i[1])
		tab[0] = '-';
	return (tab);
}

static int	exit_hook(void)
{
	//free all
	exit(0);
}

int	ft_delay(int *timer, int delay)
{
	if (*timer <= delay)
	{
		*timer += 1;
		return (1);
	}
	*timer = 0;
	return (0);
}

void	collec_animation(t_vars *vars)
{
	int			y;
	int			x;
	static int	i;

	if (ft_delay(&vars->timer, 2500) == 1)
		return ;
	if (i >= COLLEC_FRAMES)
		i = 0;
	y = -1;
	while (vars->map[++y])
	{
		x = -1;
		while (vars->map[y][++x])
			if (vars->map[y][x] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.collec[i], x * IMG_SIZE, y * IMG_SIZE);
	}
	i++;
}

int	frames(t_vars *vars)
{
	collec_animation(vars);
	return (0);
}

void	check_collec(t_vars *vars)
{
	int	x;
	int	y;

	y = -1;
	while (vars->map[++y] && vars->collec == 0)
	{
		x = -1;
		while (vars->map[y][++x])
			if (vars->map[y][x] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.exit[1], x * IMG_SIZE, y * IMG_SIZE);
	}
}

int	move_player(int diry, int dirx, void *psprite, t_vars *vars)
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
				mlx_put_image_to_window(vars->mlx, vars->win, psprite, IMG_SIZE * (x + dirx), IMG_SIZE * (y + diry));
				return(1);
			}
			if(vars->map[y][x] == 'P' && vars->map[y + diry][x + dirx] == 'E' && vars->collec == 0)
				exit(0);
		}
	}
	return(0);
}

void	display_moves(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_down, IMG_SIZE, IMG_SIZE * (vars->map_y - 2));
	mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_down, IMG_SIZE * 2, IMG_SIZE * (vars->map_y - 2));
	mlx_string_put(vars->mlx, vars->win, IMG_SIZE + 5, (vars->map_y - 1) * IMG_SIZE - 10, 0x44434d, "Moves:");
	mlx_string_put(vars->mlx, vars->win, IMG_SIZE + 45, (vars->map_y - 1) * IMG_SIZE - 10, 0x44434d, ft_itoa(vars->moves++));
}

int	inputs(int key, t_vars *vars)
{
	if (key == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if(key == KEY_UP)
		move_player(1, 0, vars->sprites.playerup, vars);
	else if(key == KEY_LEFT)
		move_player(0, -1, vars->sprites.playerleft, vars);
	else if(key == KEY_DOWN)
		move_player(-1, 0, vars->sprites.playerdown, vars);
	else if(key == KEY_RIGHT)
		move_player(0, 1, vars->sprites.playerright, vars);
	else
		return (0);
	display_moves(vars);
	check_collec(vars);
	return (0);
}

int	get_map_height(t_vars *vars)
{
	int	fd;
	int	i;
	char	*line;

	i = 1;
	fd = open(vars->mapname, 0);
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

char	**create_map(t_vars *vars)
{
	char	**map;
	int	fd;
	int	i;

	i = 0;
	vars->map_y = get_map_height(vars);
	fd = open(vars->mapname, 0);
	map = malloc(sizeof(char*) * vars->map_y);
	map[0] = get_next_line(fd);
	vars->map_x = ft_strlen_n(map[0]) + 1;
	while(++i < vars->map_y)
		map[i] = get_next_line(fd);
	close(fd);
	return (map);
}

t_sprites	get_sprites(t_vars vars)
{
	t_sprites sprites;
	char	*floor_path = "./sprites/floor.xpm";
	char	*wall_path = "./sprites/wall.xpm";
	char	*wall_upleft_path = "./sprites/wall_upleft.xpm";
	char	*wall_up_path = "./sprites/wall_up.xpm";
	char	*wall_upright_path = "./sprites/wall_upright.xpm";
	char	*wall_left_path = "./sprites/wall_left.xpm";
	char	*wall_right_path = "./sprites/wall_right.xpm";
	char	*wall_down_path = "./sprites/wall_down.xpm";
	char	*wall_downright_path = "./sprites/wall_downright.xpm";
	char	*wall_downleft_path = "./sprites/wall_downleft.xpm";
	char	*collec0_path = "./sprites/collec0.xpm";
	char	*collec1_path = "./sprites/collec1.xpm";
	char	*collec2_path = "./sprites/collec2.xpm";
	char	*collec3_path = "./sprites/collec3.xpm";
	char	*playerup_path = "./sprites/playerup.xpm";
	char	*playerdown_path = "./sprites/playerdown.xpm";
	char	*playerleft_path = "./sprites/playerleft.xpm";
	char	*playerright_path = "./sprites/playerright.xpm";
	char	*exit0_path = "./sprites/exit0.xpm";
	char	*exit1_path = "./sprites/exit1.xpm";
	int	img_width;
	int	img_height;

	sprites.floor = mlx_xpm_file_to_image(vars.mlx, floor_path, &img_width, &img_height);
	sprites.collec[0] = mlx_xpm_file_to_image(vars.mlx, collec0_path, &img_width, &img_height);
	sprites.collec[1] = mlx_xpm_file_to_image(vars.mlx, collec1_path, &img_width, &img_height);
	sprites.collec[2] = mlx_xpm_file_to_image(vars.mlx, collec2_path, &img_width, &img_height);
	sprites.collec[3] = mlx_xpm_file_to_image(vars.mlx, collec3_path, &img_width, &img_height);
	sprites.playerup = mlx_xpm_file_to_image(vars.mlx, playerup_path, &img_width, &img_height);
	sprites.playerdown = mlx_xpm_file_to_image(vars.mlx, playerdown_path, &img_width, &img_height);
	sprites.playerleft = mlx_xpm_file_to_image(vars.mlx, playerleft_path, &img_width, &img_height);
	sprites.playerright = mlx_xpm_file_to_image(vars.mlx, playerright_path, &img_width, &img_height);
	sprites.exit[0] = mlx_xpm_file_to_image(vars.mlx, exit0_path, &img_width, &img_height);
	sprites.exit[1] = mlx_xpm_file_to_image(vars.mlx, exit1_path, &img_width, &img_height);
	sprites.wall = mlx_xpm_file_to_image(vars.mlx, wall_path, &img_width, &img_height);
	sprites.wall_up = mlx_xpm_file_to_image(vars.mlx, wall_up_path, &img_width, &img_height);
	sprites.wall_upleft = mlx_xpm_file_to_image(vars.mlx, wall_upleft_path, &img_width, &img_height);
	sprites.wall_upright = mlx_xpm_file_to_image(vars.mlx, wall_upright_path, &img_width, &img_height);
	sprites.wall_left = mlx_xpm_file_to_image(vars.mlx, wall_left_path, &img_width, &img_height);
	sprites.wall_right = mlx_xpm_file_to_image(vars.mlx, wall_right_path, &img_width, &img_height);
	sprites.wall_down = mlx_xpm_file_to_image(vars.mlx, wall_down_path, &img_width, &img_height);
	sprites.wall_downleft = mlx_xpm_file_to_image(vars.mlx, wall_downleft_path, &img_width, &img_height);
	sprites.wall_downright = mlx_xpm_file_to_image(vars.mlx, wall_downright_path, &img_width, &img_height);
	return (sprites);
}

void	print_wall(t_vars *vars, int x, int y)
{
	if (y == 0)
	{
		if (x == 0)
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_upleft, IMG_SIZE * x, IMG_SIZE * y);
		else if (x == vars->map_x - 1)
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_upright, IMG_SIZE * x, IMG_SIZE * y);
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_up, IMG_SIZE * x, IMG_SIZE * y);
	}
	else if (y == vars->map_y - 2)
	{
		if (x == 0)
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_downleft, IMG_SIZE * x, IMG_SIZE * y);
		else if (x == vars->map_x - 1)
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_downright, IMG_SIZE * x, IMG_SIZE * y);
		else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_down, IMG_SIZE * x, IMG_SIZE * y);
	}
	else if (x == 0)
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_left, IMG_SIZE * x, IMG_SIZE * y);
	else if (x == vars->map_x - 1)
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall_right, IMG_SIZE * x, IMG_SIZE * y);
	else
			mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.wall, IMG_SIZE * x, IMG_SIZE * y);
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
			if(vars->map[y][x] == '1')
				print_wall(vars, x, y);
			if(vars->map[y][x] == '0')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.floor, IMG_SIZE * x, IMG_SIZE * y);
			if(vars->map[y][x] == 'P')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.playerup, IMG_SIZE * x, IMG_SIZE * y);
			if(vars->map[y][x] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.exit[0], IMG_SIZE * x, IMG_SIZE * y);
			if(vars->map[y][x] == 'C')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, vars->sprites.collec[0], IMG_SIZE * x, IMG_SIZE * y);
				vars->collec++;
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (1);
	vars.mapname = av[1];
	vars.mlx = mlx_init();
	vars.collec = 0;
	vars.moves = 0;
	vars.timer = 0;
	vars.sprites = get_sprites(vars);
	vars.map = create_map(&vars);
	vars.win = mlx_new_window(vars.mlx, IMG_SIZE * vars.map_x, IMG_SIZE * (vars.map_y - 1), "Super Romil!");
	mlx_key_hook(vars.win, inputs, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	print_map(&vars);
	mlx_loop_hook(vars.mlx, frames, &vars);
	mlx_loop(vars.mlx);
}
