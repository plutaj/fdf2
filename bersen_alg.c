/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bersen_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:04:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/15 16:30:13 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

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
    *x += ((MAP_WIDTH - map->points_width * POINT_DISTANCE) / 2);
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
    
    if (map->colour_matrix[(int)y][(int)x])
        map->colour = map->colour_matrix[(int)y][(int)x];
    else if (map->colour_matrix[(int)y1][(int)x1])
        map->colour = map->colour_matrix[(int)y1][(int)x1];
    else
    {
        if (z || z1)
            map->colour = SECOND_COLOUR;
        else 
            map->colour = WHITE_PIX;
    }
    
    incrs_poin_dist(&x, &y, &x1, &y1);
    isometric(&x, &y, z, map);
    isometric(&x1, &y1, z1, map);
    x_dest = x1 - x;
    y_dest = y1 - y;
    result = is_greater(is_negat(x_dest), is_negat(y_dest));
    x_dest /= result;
    y_dest /= result;
    while((int)(x - x1) || (int)(y - y1))
        my_put_pixel(&x, &y, x_dest, y_dest, map);
}

void    my_put_pixel(float *x, float *y, float x_dest, float y_dest, s_fdf *map)
{
    int pixel_index;
    
    pixel_index = (int)(*y) * map->size_line + (int)(*x) * (map->bpp / 8);
    *(unsigned int *)(map->mlx_img_data + pixel_index) = map->colour;
    *x += x_dest;
    *y += y_dest;
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
