/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:50:47 by thgabell          #+#    #+#             */
/*   Updated: 2023/04/05 19:48:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	scale(t_fdf *s_fdf)
{
	while (s_fdf->img_width * s_fdf->img_height < \
			s_fdf->s_map.width * s_fdf->s_map.height * s_fdf->zoom)
		s_fdf->zoom--;
}

void	quit_error(char *str, t_fdf *s_fdf)
{
	ft_putstr_fd(str, 1);
	quit(s_fdf);
	exit (1);
}

int	quit(t_fdf *s_fdf)
{
	if (s_fdf->img_ptr)
	{
		mlx_destroy_image(s_fdf->mlx_ptr, s_fdf->img_ptr);
		mlx_destroy_window(s_fdf->mlx_ptr, s_fdf->win_ptr);
		mlx_destroy_display(s_fdf->mlx_ptr);
		free(s_fdf->mlx_ptr);
	}
	if (s_fdf->s_map.height > 0)
	{
		while (--s_fdf->s_map.height >= 0)
			free(s_fdf->s_map.points[s_fdf->s_map.height]);
		free(s_fdf->s_map.points);
	}
	free(s_fdf);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_fdf	*s_fdf;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <filename>", 1);
		return (0);
	}		
	s_fdf = malloc(sizeof(t_fdf));
	if (!s_fdf)
		return (0);
	init_fdf(s_fdf);
	if (read_map(s_fdf, argv[1]))
	{
		scale(s_fdf);
		center(s_fdf);
		draw(s_fdf);
		mlx_hook(s_fdf->win_ptr, 2, (1L << 0), deal_keyboard, s_fdf);
		mlx_hook(s_fdf->win_ptr, 17, 0, quit, s_fdf);
		mlx_mouse_hook(s_fdf->win_ptr, deal_mouse, s_fdf);
		mlx_loop(s_fdf->mlx_ptr);
	}
	quit(s_fdf);
}
