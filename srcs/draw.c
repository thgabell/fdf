/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgabell <thgabell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:44:27 by thgabell          #+#    #+#             */
/*   Updated: 2023/03/29 19:56:44 by thgabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))
#define SGN(_x) ((_x) < 0 ? -1 : ((_x) > 0 ? 1 : 0))

void	my_mlx_pixel_put(t_fdf *s_fdf, int x, int y, int color)
{
	char	*dst;

	dst = s_fdf->addr + (y * s_fdf->line_length + x * (s_fdf->bpp/ 8));
	*(unsigned int*)dst = color;
}

int	check_limits(t_fdf *s_fdf, int x, int y)
{
	if (s_fdf->img_width - 1 < x || x < 0)
		return (0);
	if (s_fdf->img_height - 1 < y || y < 0)
		return (0);
	return (1);
}

void draw_line(t_fdf *s_fdf, int x0, int y0, int x1, int y1)
		{
			int dx = x1 - x0;
			int dy = y1 - y0;
			int incX = SGN(dx);
			int incY = SGN(dy);
			dx = ABS(dx);
			dy = ABS(dy);

			if (dy == 0)
			{
				// horizontal line
				for (int x = x0; x != x1 + incX; x += incX)
					my_mlx_pixel_put(s_fdf, x, y0, 0xFFFFFF);
			}
			else if (dx == 0)
			{
				// vertical line
				for (int y = y0; y != y1 + incY; y += incY)
					my_mlx_pixel_put(s_fdf, x0, y, 0xFFFFFF);
			}
			else if (dx >= dy)
			{
				// more horizontal than vertical
				int slope = 2 * dy;
				int error = -dx;
				int errorInc = -2 * dx;
				int y = y0;

				for (int x = x0; x != x1 + incX; x += incX)
				{
					my_mlx_pixel_put(s_fdf, x, y, 0xFFFFFF);
					error += slope;

					if (error >= 0)
					{
						y += incY;
						error += errorInc;
					}
				}
			}
			else
			{
				// more vertical than horizontal
				int slope = 2 * dx;
				int error = -dy;
				int errorInc = -2 * dy;
				int x = x0;

				for (int y = y0; y != y1 + incY; y += incY)
				{
					my_mlx_pixel_put(s_fdf, x, y, 0xFFFFFF);
					error += slope;

					if (error >= 0)
					{
						x += incX;
						error += errorInc;
					}
				}
			}
		}


void draw(t_fdf *s_fdf) {
    int	i;
	int	j;

	i = 0;
    while (i < s_fdf->s_map.height)
	{
		j = 0;
        while (j < s_fdf->s_map.width)
		{
			if (j < s_fdf->s_map.width - 1) {
				draw_line(s_fdf, j * s_fdf->zoom + s_fdf->x_translate, i * s_fdf->zoom + s_fdf->y_translate, (j + 1) * s_fdf->zoom + s_fdf->x_translate, i * s_fdf->zoom + s_fdf->y_translate);
			}
			if (i < s_fdf->s_map.height - 1) {
				draw_line(s_fdf, j * s_fdf->zoom + s_fdf->x_translate, i * s_fdf->zoom + s_fdf->y_translate, j * s_fdf->zoom + s_fdf->x_translate, (i + 1) * s_fdf->zoom + s_fdf->y_translate);
			}
			j++;
        }
		i++;
    }
	mlx_put_image_to_window(s_fdf->mlx_ptr, s_fdf->win_ptr, s_fdf->img_ptr, 0, 0);
}
