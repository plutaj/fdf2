/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bersen_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:04:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/17 16:39:09 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_fdf *map)
{
	t_crds crds;

	crds.y = 0;
	while (crds.y < map->points_height)
	{
		crds.x = 0;
		while (crds.x < map->points_width)
		{
			if (crds.x < map->points_width - 1)
				bersenham(&crds, map, 1);
			if (crds.y < map->points_height - 1)
				bersenham(&crds, map, 2);
			crds.x++;
		}
		crds.y++;
	}
}

void	copy_data(t_crds *temp, t_crds *crds)
{
	temp->x = crds->x;
	temp->y = crds->y;
	temp->x1 = crds->x1;
	temp->y1 = crds->y1;
}

void	bersenham(t_crds *crds, t_fdf *map, int i)
{
	float	x_dest;
	float	y_dest;
	int		result;
	int		z;
	int		z1;
	t_crds 	temp;

	if (i == 1)
	{
		crds->x1 = crds->x + 1;
		crds->y1 = crds->y;
	}
	else if (i == 2)
	{
		crds->y1 = crds->y + 1;
		crds->x1 = crds->x;
	}
	z = map->matrix[(int)crds->y][(int)crds->x];
	z1 = map->matrix[(int)crds->y1][(int)crds->x1];
	colour_handling(crds, z, z1, map);
	copy_data(&temp, crds);
	incrs_poin_dist(&temp);
	isometric(&temp.x, &temp.y, z, map);
	isometric(&temp.x1, &temp.y1, z1, map);
	x_dest = temp.x1 - temp.x;
	y_dest = temp.y1 - temp.y;
	result = is_greater(is_negat(x_dest), is_negat(y_dest));
	x_dest /= result;
	y_dest /= result;
	while ((int)(temp.x - temp.x1) || (int)(temp.y - temp.y1))
		my_put_pixel(&temp, x_dest, y_dest, map);
}

void	my_put_pixel(t_crds *temp, float x_dest, float y_dest, t_fdf *map)
{
	int	pixel_index;

	pixel_index = (int)(temp->y) * map->size_line + (int)(temp->x) * (map->bpp / 8);
	*(unsigned int *)(map->mlx_img_data + pixel_index) = map->colour;
	temp->x += x_dest;
	temp->y += y_dest;
}

void	incrs_poin_dist(t_crds *temp)
{
	temp->x *= POINT_DISTANCE;
	temp->y *= POINT_DISTANCE;
	temp->x1 *= POINT_DISTANCE;
	temp->y1 *= POINT_DISTANCE;
}
