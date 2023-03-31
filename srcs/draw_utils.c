/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgabell <thgabell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:28:18 by thgabell          #+#    #+#             */
/*   Updated: 2023/03/31 17:29:29 by thgabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_border(t_fdf *s_fdf, int x, int y)
{
	if (s_fdf->img_width - 1 < x || x < 0)
		return (0);
	if (s_fdf->img_height - 1 < y || y < 0)
		return (0);
	return (1);
}

void	my_mlx_pixel_put(t_fdf *s_fdf, int x, int y, int color)
{
	char	*dst;

	dst = s_fdf->addr + (y * s_fdf->line_length + x * (s_fdf->bpp / 8));
	*(unsigned int *)dst = color;
}
