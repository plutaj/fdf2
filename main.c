/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:26:48 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/12 20:29:45 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
    void    *mlx_connection;
    void    *mlx_window;
    s_fdf   *map;

    if (argc != 2)
        exit(1);
    map = (s_fdf *)malloc(sizeof(s_fdf));
    get_width_height(map, argv[1]);
    alloc_matrix(map, argv[1]);
    map->mlx_connection = mlx_init();
    map->mlx_window = mlx_new_window(map->mlx_connection, MAP_WIDTH, MAP_HEIGHT, "FdF");
    print_map(map);
    mlx_key_hook(map->mlx_window, get_inpt, map);
    mlx_hook(map->mlx_window, 17, 0, close_window, map);
    mlx_loop(map->mlx_connection);
    return (0);
}

// void free_all(s_fdf *map)
// {
//     int i;

//     if (map->mlx_window)
//         mlx_destroy_window(map->mlx_connection, map->mlx_window);
//     // if (map->mlx_connection)
//     //     mlx_destroy_display(map->mlx_connection);
//     if (map->matrix) {
//         for (i = 0; i < map->points_height; i++) {
//             free(map->matrix[i]);
//         }
//         free(map->matrix);
//     }
//     if (map->colour_matrix) {
//         for (i = 0; i < map->points_height; i++) {
//             free(map->colour_matrix[i]);
//         }
//         free(map->colour_matrix);
//     }
//     if (map->mlx_connection)
//         free(map->mlx_connection);
//     if (map->mlx_window)
//         free(map->mlx_window);
//     if (map)
//         free(map);
// }

void free_all(s_fdf *map)
{
    if (map)
    {
        free_matrixes(map);
        if (map->mlx_window)
        {
            mlx_destroy_window(map->mlx_connection, map->mlx_window);
            map->mlx_window = NULL;
        }
        if (map->mlx_connection)
        {
            free(map->mlx_connection);
            map->mlx_connection = NULL;
        }
        free(map);
    }
}

void    free_matrixes(s_fdf *map)
{
    int i;

    i = 0;
    if (map->matrix)
    {
        while (i < map->points_height)
        {
            free(map->matrix[i]);
            i++;
        }
        free(map->matrix);
    }
    i = 0;
    if (map->colour_matrix)
    {
        while (i < map->points_height)
        {
            free(map->colour_matrix[i]);
            i++;
        }
        free(map->colour_matrix);
    }
}

int get_inpt(int key, s_fdf *map)
{
    if (key == 53)
    {
        free_all(map);
        exit(0);
    }
    return (0);
}

int close_window(s_fdf *map)
{
    free_all(map);
    exit(0);
    return (0);
}
