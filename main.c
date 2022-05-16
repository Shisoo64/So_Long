#include "so_long.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*relative_path = "./sprites/floor.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, img, 0, 16);
	mlx_put_image_to_window(mlx, mlx_win, img, 16, 0);
	mlx_put_image_to_window(mlx, mlx_win, img, 16, 16);
	mlx_loop(mlx);
}
