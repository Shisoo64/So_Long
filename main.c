#include "so_long.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

void	printRow(t_vars vars, void *img, char *str)
{
	int	i;

	i = -1;
	while(str[++i])
		if(str[i] == '1')
			mlx_put_image_to_window(vars.mlx, vars.win, img, 16 * i, 0);
}

int	main(void)
{
	t_vars	vars;
	void	*img_floor;
	char	*relative_path = "./sprites/floor.xpm";
	int		img_width;
	int		img_height;

	vars.mlx = mlx_init();
	img_floor = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
	
	vars.win = mlx_new_window(vars.mlx, img_width*16, img_height*16, "Super Romil!");
	
	printRow(vars, img_floor, "000111001010");
	
	mlx_loop(vars.mlx);
}
