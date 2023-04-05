#include "fdf.h"

void	new_image(t_fdf *s_fdf)
{
	mlx_destroy_image(s_fdf->mlx_ptr, s_fdf->img_ptr);
	s_fdf->img_ptr = mlx_new_image(s_fdf->mlx_ptr, \
						s_fdf->img_width, s_fdf->img_height);
	draw(s_fdf);
}

void	center(t_fdf *s_fdf)
{
	if (s_fdf->iso)
	{
		s_fdf->x_translate = (s_fdf->img_width / 2);
		s_fdf->y_translate = (s_fdf->img_height / 2) \
		- (s_fdf->s_map.height * s_fdf->zoom / 2);
	}
	else
	{
		s_fdf->x_translate = (s_fdf->img_width / 2) \
		- (s_fdf->s_map.width * s_fdf->zoom / 2);
		s_fdf->y_translate = (s_fdf->img_height / 2) \
		- (s_fdf->s_map.height * s_fdf->zoom / 2);
	}
	new_image(s_fdf);
}

void	flatten(t_fdf *s_fdf, int key)
{
	if (key == U)
		s_fdf->z_divisor -= 0.1;
	else if (key == D)
		s_fdf->z_divisor += 0.1;
	if (s_fdf->z_divisor < 0.1)
		s_fdf->z_divisor = 0.1;
	else if (s_fdf->z_divisor > 10)
		s_fdf->z_divisor = 10;
	new_image(s_fdf);
}

void	translate(t_fdf *s_fdf, int key)
{
	if (key == ARROW_UP)
		s_fdf->y_translate -= 10;
	else if (key == ARROW_DOWN)
		s_fdf->y_translate += 10;
	else if (key == ARROW_LEFT)
		s_fdf->x_translate += 10;
	else if (key == ARROW_RIGHT)
		s_fdf->x_translate -= 10;
	new_image(s_fdf);
}

void	zoom(t_fdf *s_fdf, int key)
{
	if ((key == MINUS || key == NUM_MINUS || \
		key == WHEEL_DOWN) && s_fdf->zoom > 2)
		s_fdf->zoom--;
	else if (key == PLUS || key == NUM_PLUS || key == WHEEL_UP)
		s_fdf->zoom++;
	new_image(s_fdf);
}
