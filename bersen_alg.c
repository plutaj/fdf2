/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bersen_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:04:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/10 17:01:12 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    print_map(s_fdf *map)
{
    int    x;
    int    y;

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

void    isometric(float *x, float *y, int z, s_fdf *map)
{
    *x = (*x - *y) * cos(0.8);
    *y = (*x + *y) * sin(0.8) - z;
    padding(x, y, map);
}

void    padding(float *x, float *y, s_fdf *map)
{
    *x += ((MAP_WIDTH - map->points_width * POINT_DISTANCE) * 1.2);
    *y += (MAP_HEIGHT - map->points_height * POINT_DISTANCE) / 2;
}

void    bersenham(float x, float y, float x1, float y1, s_fdf *map)
{
    float   x_dest;
    float   y_dest;
    int     result;
    int     z;
    int     z1;

    z = map->matrix[(int)y][(int)x];
    z1 = map->matrix[(int)y1][(int)x1];
    incrs_poin_dist(&x, &y, &x1, &y1);
    if (z)
        map->colour = 0xFF0000;
    else
        map->colour = WHITE_PIX;
    isometric(&x, &y, z, map);
    isometric(&x1, &y1, z1, map);
    x_dest = x1 - x;
    y_dest = y1 - y;
    result = is_greater(is_negat(x_dest), is_negat(y_dest));
    x_dest /= result;
    y_dest /= result;
    while((int)(x - x1) || (int)(y - y1))
    {
        mlx_pixel_put(map->mlx_connection, map->mlx_window, x, y, map->colour);
        x += x_dest;
        y += y_dest;
    }
}

float   is_greater(float x, float y)
{
    if (x > y)
        return (x);
    else
        return (y);
}

float   is_negat(float n)
{
    if (n < 0)
        return (-n);
    else
        return (n);
}

void    incrs_poin_dist(float *x, float *y, float *x1, float *y1)
{
    *x *= POINT_DISTANCE;
    *y *= POINT_DISTANCE;
    *x1 *= POINT_DISTANCE;
    *y1 *= POINT_DISTANCE;
}
