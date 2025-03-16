/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:40:52 by jpluta            #+#    #+#             */
/*   Updated: 2025/03/16 13:53:23 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_temp_colour_line(char **temp_colour_line)
{
	int	i;

	i = 0;
	while (temp_colour_line[i])
	{
		free(temp_colour_line[i]);
		i++;
	}
	free(temp_colour_line);
	temp_colour_line = NULL;
}

void	free_all(s_fdf *map)
{
	if (map)
	{
		free_matrixes(map);
		if (map->mlx_window)
		{
			mlx_destroy_window(map->mlx_connection, map->mlx_window);
			map->mlx_window = NULL;
		}
		if (map->mlx_image)
		{
			mlx_destroy_image(map->mlx_connection, map->mlx_image);
			map->mlx_image = NULL;
		}
		if (map->mlx_connection)
		{
			mlx_destroy_display(map->mlx_connection);
			if (map->mlx_connection)
				free(map->mlx_connection);
			map->mlx_connection = NULL;
		}
		free(map);
		map = NULL;
	}
}

void    free_matrixes(s_fdf *map)
{
    int i;

    i = map->points_height;
    if (map->matrix)
    {
        while (i >= 0)
        {
            free(map->matrix[i]);
			map->matrix[i] = NULL;
			i--;
        }
        free(map->matrix);
    }
    i = map->points_height;
    if (map->colour_matrix)
    {
        while (i >= 0)
        {
			free(map->colour_matrix[i]);
			map->colour_matrix[i] = NULL;
			i--;
        }
        free(map->colour_matrix);
    }
}
