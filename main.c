/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:26:48 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/14 20:16:08 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
    s_fdf   *map;

    edge_cases(argc, argv[1]);
    map = (s_fdf *)malloc(sizeof(s_fdf));
    get_width_height(map, argv[1]);
    alloc_matrix(map, argv[1]);
    get_mlx_data(map, argv[1]);
    print_map(map);
    mlx_put_image_to_window(map->mlx_connection, map->mlx_window, map->mlx_image, 0, 0);
    
    mlx_key_hook(map->mlx_window, get_inpt, map);
    mlx_hook(map->mlx_window, 17, 0, close_window, map);
    
    mlx_loop(map->mlx_connection);
    return (0);
}

void    edge_cases(int argc, char *argv)
{
    int     fd;
    int     i;

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

void    get_mlx_data(s_fdf *map, char *name)
{
    map->mlx_connection = mlx_init();
    map->mlx_window = mlx_new_window(map->mlx_connection, MAP_WIDTH + 100, MAP_HEIGHT + 100, name);
    map->mlx_image = mlx_new_image(map->mlx_connection, MAP_WIDTH, MAP_HEIGHT);
    map->mlx_img_data = mlx_get_data_addr(map->mlx_image, &map->bpp, &map->size_line, &map->endian);
}

void free_all(s_fdf *map)
{
    if (map)
    {
        free_matrixes(map);
        if (map->mlx_window)
        {
            mlx_destroy_window(map->mlx_connection, map->mlx_window);
            // if (map->mlx_window)
            //     free(map->mlx_window);
            map->mlx_window = NULL;
        }
        if (map->mlx_image)
        {
            mlx_destroy_image(map->mlx_connection, map->mlx_image);
            // if (map->mlx_image)
            //     free(map->mlx_image);
            map->mlx_image = NULL;
        }
        if (map->mlx_connection)
        {
            mlx_destroy_display(map->mlx_connection);
            if (map->mlx_connection)
                free(map->mlx_connection);
        }
        free(map);
    }
}

// void    free_matrixes(s_fdf *map)
// {
//     int i;

//     i = 0;
//     if (map->matrix)
//     {
//         while (i < map->points_height)
//         {
//             free(map->matrix[i]);
//             i++;
//         }
//         free(map->matrix);
//     }
//     i = 0;
//     if (map->colour_matrix)
//     {
//         while (i < map->points_height)
//         {
//             free(map->colour_matrix[i]);
//             i++;
//         }
//         free(map->colour_matrix);
//     }
// }

void    free_matrixes(s_fdf *map)
{
    int i;

    i = 0;
    if (map->matrix)
    {
        while (map->matrix[i])
        {
            free(map->matrix[i]);
            i++;
        }
        free(map->matrix);
    }
    i = 0;
    if (map->colour_matrix)
    {
        while (map->colour_matrix[i])
        {
            free(map->colour_matrix[i]);
            i++;
        }
        free(map->colour_matrix);
    }
}

int get_inpt(int key, s_fdf *map)
{
    if (key == XK_Escape)
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
