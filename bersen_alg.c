/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bersen_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:04:10 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/09 16:36:34 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    bersenham(float x, float y, float x1, float y1, s_fdf *map_data)
{
    float   x_dest;
    float   y_dest;
    int     result;

    x_dest = x1 - x;
    y_dest = y1 - y;
    
    result = is_greater(is_negat(x_dest), is_negat(y_dest));
    x_dest /= result;
    y_dest /= result;
    while((int)(x - x1) || (int)(y - y1))
    {
        mlx_pixel_put(map_data->mlx_connection, map_data->mlx_window, x, y, WHITE_PIX);
        x+= x_dest;
        y+=y_dest;
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