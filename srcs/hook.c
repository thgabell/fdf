/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgabell <thgabell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:12:20 by thgabell          #+#    #+#             */
/*   Updated: 2023/03/31 17:16:09 by thgabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_keyboard(int key, t_fdf *s_fdf)
{
	if (key == ESCAPE)
		quit(s_fdf);
	else if (key == PLUS || key == NUM_PLUS || key == MINUS || key == NUM_MINUS)
		zoom(s_fdf, key);
	else if (key == ARROW_DOWN || key == ARROW_UP || \
			key == ARROW_LEFT || key == ARROW_RIGHT)
		translate(s_fdf, key);
	else if (key == U || key == D)
		flatten(s_fdf, key);
	else if (key == TAB)
	{
		if (s_fdf->iso)
			s_fdf->iso = 0;
		else
			s_fdf->iso = 1;
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
	if (key == WHEEL_UP || key == WHEEL_DOWN)
		zoom(s_fdf, key);
	ft_putnbr_fd(key, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
