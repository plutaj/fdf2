#include "fdf.h"

int main(int argc, char **argv)
{
    void    *mlx_connection;
    void    *mlx_window;
    s_fdf   *map;

    if (argc != 2)
        exit(1);
    map = (s_fdf *)malloc(sizeof(s_fdf));
    fill_map(map, argv[1]);
    printf("%d\n", map->points_height);
    printf("%d", map->points_width);
    return (0);
}