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
    map->mlx_window = mlx_new_window(map->mlx_connection, MAP_WIDTH + (map->points_width * PIXEL_DISTANCE), 
                                    MAP_HEIGHT + (map->points_height * PIXEL_DISTANCE), "FdF");
    
    // TEST
    // int i = 0;
    // int y = 0;
    // while (map->points_height > i)
    // {
    //     while (map->points_width > y)
    //     {
    //         printf("%d ", map->matrix[i][y]);
    //         y++;
    //     }
    //     y = 0;
    //     printf("\n");
    //     i++;
    // }
    // TEST
    return (0);
}

