/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bersen_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:04:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/16 15:49:18 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_fdf *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->points_height)
	{
		x = 0;
		while (x < map->points_width)
		{
			if (x < map->points_width - 1)
				bersenham(x, y, x + 1, y, map);
			if (y < map->points_height - 1)
				bersenham(x, y, x, y + 1, map);
			x++;
		}
		y++;
	}
}

void	bersenham(float x, float y, float x1, float y1, t_fdf *map)
{
	float	x_dest;
	float	y_dest;
	int		result;
	int		z;
	int		z1;

	z = map->matrix[(int)y][(int)x];
	z1 = map->matrix[(int)y1][(int)x1];
	colour_handling(x, y, x1, y, z, z1, map);
	incrs_poin_dist(&x, &y, &x1, &y1);
	isometric(&x, &y, z, map);
	isometric(&x1, &y1, z1, map);
	x_dest = x1 - x;
	y_dest = y1 - y;
	result = is_greater(is_negat(x_dest), is_negat(y_dest));
	x_dest /= result;
	y_dest /= result;
	while ((int)(x - x1) || (int)(y - y1))
		my_put_pixel(&x, &y, x_dest, y_dest, map);
}

void	my_put_pixel(float *x, float *y, float x_dest, float y_dest, t_fdf *map)
{
	int	pixel_index;

	pixel_index = (int)(*y) * map->size_line + (int)(*x) * (map->bpp / 8);
	*(unsigned int *)(map->mlx_img_data + pixel_index) = map->colour;
	*x += x_dest;
	*y += y_dest;
}

void	incrs_poin_dist(float *x, float *y, float *x1, float *y1)
{
	*x *= POINT_DISTANCE;
	*y *= POINT_DISTANCE;
	*x1 *= POINT_DISTANCE;
	*y1 *= POINT_DISTANCE;
}
