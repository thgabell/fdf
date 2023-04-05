/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:14:48 by thgabell          #+#    #+#             */
/*   Updated: 2023/04/05 20:49:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_width(char **splited)
{
	int	width;

	width = 0;
	while (splited[width] && splited[width][0] != '\n')
		width++;
	return (width);
}

static void	add_line(t_fdf *s_fdf)
{
	int	i;
	int	**s_tmp;

	i = 0;
	s_tmp = malloc(sizeof(int *) * (s_fdf->s_map.height + 1));
	if (!s_tmp)
		return ;
	while (i < s_fdf->s_map.height)
	{
		s_tmp[i] = s_fdf->s_map.points[i];
		i++;
	}
	s_tmp[i] = malloc(sizeof(int) * s_fdf->s_map.width);
	if (!s_tmp[i])
		return ;
	free(s_fdf->s_map.points);
	s_fdf->s_map.points = s_tmp;
}

static void	fill_points(t_fdf *s_fdf, char **splited)
{
	int		i;

	if (s_fdf->s_map.height == 0)
	{
		s_fdf->s_map.points = malloc(sizeof(int *));
		if (!s_fdf->s_map.points)
			return ;
		s_fdf->s_map.points[0] = malloc(sizeof(int) * s_fdf->s_map.width);
		if (!s_fdf->s_map.points[s_fdf->s_map.height])
		{
			free(s_fdf->s_map.points);
			return ;
		}
	}
	else
		add_line(s_fdf);
	i = 0;
	while (i < s_fdf->s_map.width)
	{
		s_fdf->s_map.points[s_fdf->s_map.height][i] = ft_atoi(splited[i]);
		i++;
	}
	s_fdf->s_map.height++;
}

int	read_map(t_fdf *s_fdf, char *argv)
{
	int		i;
	int		fd;
	char	*line;
	char	**splited;

	fd = open(argv, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL && s_fdf->s_map.height == 0)
			quit_error("Invalid file.", s_fdf);
		if (line == NULL)
			break ;
		splited = ft_split(line, ' ');
		s_fdf->s_map.width = get_width(splited);
		fill_points(s_fdf, splited);
		i = 0;
		while (splited[i])
			free(splited[i++]);
		free(splited);
		free(line);
	}
	return (1);
}

void	init_fdf(t_fdf *s_fdf)
{
	s_fdf->mlx_ptr = mlx_init();
	s_fdf->win_ptr = mlx_new_window(s_fdf->mlx_ptr, 1920, 1080, "FDF");
	s_fdf->img_width = 1920;
	s_fdf->img_height = 1080;
	s_fdf->img_ptr = mlx_new_image(s_fdf->mlx_ptr, \
					s_fdf->img_width, s_fdf->img_height);
	s_fdf->addr = mlx_get_data_addr(s_fdf->img_ptr, &s_fdf->bpp, \
					&s_fdf->line_length, &s_fdf->endian);
	s_fdf->z_divisor = 1;
	s_fdf->iso = 1;
	s_fdf->zoom = 20;
	s_fdf->s_map.width = 0;
	s_fdf->s_map.height = 0;
	s_fdf->s_map.points = NULL;
}
