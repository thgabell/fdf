/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgabell <thgabell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:50:47 by thgabell          #+#    #+#             */
/*   Updated: 2023/03/24 19:11:18 by thgabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *s_fdf, int x, int y, int color)
{
	char	*dst;

	dst = s_fdf->addr + (y * s_fdf->line_length + x * (s_fdf->bpp/ 8));
	*(unsigned int*)dst = color;
}

void	quit(t_fdf *s_fdf)
{
		mlx_destroy_image(s_fdf->mlx_ptr, s_fdf->img_ptr);
		mlx_destroy_window(s_fdf->mlx_ptr, s_fdf->win_ptr);
		mlx_destroy_display(s_fdf->mlx_ptr);
		while (--s_fdf->s_map.height >= 0)
			free(s_fdf->s_map.points[s_fdf->s_map.height]);
		free(s_fdf->s_map.points);
		free(s_fdf->mlx_ptr);
		free(s_fdf);
		exit(0);
}

int	deal_key(int key, t_fdf *s_fdf)
{
	if (key == 65307)
		quit(s_fdf);
	return (0);
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
		my_mlx_pixel_put(s_fdf, 5, 5, 0x00FF0000);
		mlx_put_image_to_window(s_fdf->mlx_ptr, s_fdf->win_ptr, s_fdf->img_ptr, 0, 0);
		mlx_key_hook(s_fdf->win_ptr, deal_key, s_fdf);
		mlx_loop(s_fdf->mlx_ptr);
	
	}	
	free(s_fdf);
}
