/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:43:12 by jpluta            #+#    #+#             */
/*   Updated: 2025/03/16 13:54:35 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_mlx_data(s_fdf *map, char *name)
{
	map->mlx_connection = mlx_init();
	map->mlx_window = mlx_new_window(map->mlx_connection,
			MAP_WIDTH + 100, MAP_HEIGHT + 100, name);
	map->mlx_image = mlx_new_image(map->mlx_connection,
			MAP_WIDTH, MAP_HEIGHT);
	map->mlx_img_data = mlx_get_data_addr(map->mlx_image,
			&map->bpp, &map->size_line, &map->endian);
}

void	edge_cases(int argc, char *argv)
{
	int	fd;
	int	i;

	i = 0;
	if (argc != 2)
		exit(1);
	while (argv[i])
		i++;
	i -= 4;
	if (argv[i] != '.' && argv[i] != 'f' && argv[i] != 'd' && argv[i] != 'f')
	{
		ft_printf("Wrong extension\n");
		exit(1);
	}
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		exit(1);
	close(fd);
}

int	find_colour(s_fdf *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->points_height)
	{
		j = 0;
		while (j < map->points_width)
		{
			if (map->colour_matrix[i][j] != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	get_inpt(int key, s_fdf *map)
{
	if (key == XK_Escape)
	{
		free_all(map);
		exit(0);
	}
	return (0);
}

int	close_window(s_fdf *map)
{
	free_all(map);
	exit(0);
	return (0);
}
