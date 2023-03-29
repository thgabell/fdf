#include "fdf.h"

void	new_image(t_fdf *s_fdf)
{
		mlx_destroy_image(s_fdf->mlx_ptr, s_fdf->img_ptr);
		s_fdf->img_ptr = mlx_new_image(s_fdf->mlx_ptr, s_fdf->img_width, s_fdf->img_height);
		draw(s_fdf);
}

int	deal_keyboard(int key, t_fdf *s_fdf)
{
	if (key == ESCAPE)
		quit(s_fdf);
	else if (key == PLUS || key == NUM_PLUS)
	{
		s_fdf->zoom++;
		new_image(s_fdf);
	}
	else if ((key == MINUS || key == NUM_MINUS) && s_fdf->zoom > 2)
	{
		s_fdf->zoom--;
		new_image(s_fdf);
	}
	else if (key == ARROW_DOWN)
	{
		s_fdf->y_translate += 10;
		new_image(s_fdf);
	}
	else if (key == ARROW_UP)
	{
		s_fdf->y_translate -= 10;
		new_image(s_fdf);
	}
	else if (key == ARROW_LEFT)
	{
		s_fdf->x_translate += 10;
		new_image(s_fdf);
	}
	else if (key == ARROW_RIGHT)
	{
		s_fdf->x_translate -= 10;
		new_image(s_fdf);
	}
	ft_putnbr_fd(key, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

int	deal_mouse(int key, int x, int y, t_fdf *s_fdf)
{
	(void) x;
	(void) y;
	if (key == WHEEL_UP)
	{
		s_fdf->zoom++;
		new_image(s_fdf);
	}
	else if (key == WHEEL_DOWN && s_fdf->zoom > 2)
	{
		s_fdf->zoom--;
		new_image(s_fdf);
	}
	return (0);
}