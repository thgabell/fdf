/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgabell <thgabell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:39:21 by thgabell          #+#    #+#             */
/*   Updated: 2023/03/23 18:22:46 by thgabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"

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
	int		bpp;
	int		line_length;
	int		endian;
	t_map	s_map;
}	t_fdf;

void	init_fdf(t_fdf *s_fdf);
int		read_map(t_fdf *s_fdf, char *argv);

#endif