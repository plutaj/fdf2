/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bersen_alg_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:38:47 by jpluta            #+#    #+#             */
/*   Updated: 2025/03/17 16:39:52 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	colour_handling(t_crds *crds, int z, int z1, t_fdf *map)
{
	if (map->true_colour == 1)
	{
		if (map->colour_matrix[(int)crds->y][(int)crds->x])
			map->colour = WHITE_PIX - (z * POINT_DISTANCE);
		else if (map->colour_matrix[(int)crds->y1][(int)crds->x1])
			map->colour = map->colour_matrix[(int)crds->y1][(int)crds->x1];
		else
			map->colour = WHITE_PIX;
	}
	else
	{
		if (z || z1)
		{
			if (z)
				map->colour = WHITE_PIX - (z * POINT_DISTANCE * 5000);
			else
				map->colour = WHITE_PIX - (z1 * POINT_DISTANCE * 5000);
		}
		else
			map->colour = WHITE_PIX;
	}
}

void	padding(float *x, float *y, t_fdf *map)
{
	*x += ((MAP_WIDTH - map->points_width * POINT_DISTANCE) / 2) / cos(0.8);
	*y += ((MAP_HEIGHT - map->points_height * POINT_DISTANCE) / 2);
}

void	isometric(float *x, float *y, int z, t_fdf *map)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
	padding(x, y, map);
}


float	is_greater(float x, float y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

float	is_negat(float n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
