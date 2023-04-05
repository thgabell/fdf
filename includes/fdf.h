/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgabell <thgabell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:39:21 by thgabell          #+#    #+#             */
/*   Updated: 2023/03/31 17:28:08 by thgabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "keys.h"

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_map
{
	int	width;
	int	height;
	int	**points;
}	t_map;

typedef struct s_fdf
{
	int		img_width;
	int		img_height;
	char	*addr;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	float	z_divisor;
	int		iso;
	int		zoom;
	int		x_translate;
	int		y_translate;
	int		color;
	int		bpp;
	int		line_length;
	int		endian;
	t_map	s_map;
}	t_fdf;

void	init_fdf(t_fdf *s_fdf);
int		read_map(t_fdf *s_fdf, char *argv);
void	draw(t_fdf *s_fdf);
void	my_mlx_pixel_put(t_fdf *s_fdf, int x, int y, int color);
int		deal_keyboard(int key, t_fdf *s_fdf);
int		deal_mouse(int key, int x, int y, t_fdf *s_fdf);
int		quit(t_fdf *s_fdf);
void    center_map(t_fdf *s_fdf);
void	quit_error(char *str, t_fdf *s_fdf);
int		check_border(t_fdf *s_fdf, int x, int y);

/* CONTROLS */

void	zoom(t_fdf *s_fdf, int key);
void	translate(t_fdf *s_fdf, int key);
void	flatten(t_fdf *s_fdf, int key);

void	new_image(t_fdf *s_fdf);

#endif