/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:44:27 by thgabell          #+#    #+#             */
/*   Updated: 2023/04/06 18:00:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	adjust_camera(t_fdf *s_fdf, t_point *p)
{
	float	prev_x;
	float	prev_y;

	p->x *= s_fdf->zoom;
	p->y *= s_fdf->zoom;
	p->z *= s_fdf->zoom;
	if (s_fdf->iso)
	{		
		prev_x = p->x;
		prev_y = p->y;
		p->x = (prev_x - prev_y) * cos(0.523599);
		p->y = -p->z + (prev_x + prev_y) * sin(0.523599);
	}
	p->x += s_fdf->x_translate;
	p->y += s_fdf->y_translate;
}

static void	draw_line(t_fdf *s_fdf, t_point start, t_point end)
{
	float	x_step;
	float	y_step;
	int		pixels;
	t_point	cur;

	start.z = s_fdf->s_map.points[(int)start.y][(int)start.x] \
				/ s_fdf->z_divisor;
	end.z = s_fdf->s_map.points[(int)end.y][(int)end.x] / s_fdf->z_divisor;
	adjust_camera(s_fdf, &start);
	adjust_camera(s_fdf, &end);
	x_step = end.x - start.x;
	y_step = end.y - start.y;
	pixels = sqrt((x_step * x_step) + (y_step * y_step));
	x_step /= pixels;
	y_step /= pixels;
	cur = start;
	while (pixels >= 0)
	{
		if (check_border(s_fdf, cur.x, cur.y))
			my_mlx_pixel_put(s_fdf, (int)cur.x, (int)cur.y, 0x00FFFFFF);
		cur.x += x_step;
		cur.y += y_step;
		pixels--;
	}
}

static void	draw_map(t_fdf *s_fdf, t_point p1, t_point p2)
{
	if (p1.x < s_fdf->s_map.width - 1)
	{
		p2.x = p1.x + 1;
		p2.y = p1.y;
		draw_line(s_fdf, p1, p2);
	}
	if (p1.y < s_fdf->s_map.height - 1)
	{
		p2.x = p1.x;
		p2.y = p1.y + 1;
		draw_line(s_fdf, p1, p2);
	}
}

void	draw(t_fdf *s_fdf)
{
	t_point	p1;
	t_point	p2;

	p1.y = 0;
	p2.x = 0;
	p2.y = 0;
	while (p1.y < s_fdf->s_map.height)
	{
		p1.x = 0;
		while (p1.x < s_fdf->s_map.width)
		{
			draw_map(s_fdf, p1, p2);
			p1.x++;
		}
		p1.y++;
	}
	mlx_put_image_to_window(s_fdf->mlx_ptr, \
							s_fdf->win_ptr, s_fdf->img_ptr, 0, 0);
}
