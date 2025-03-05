#include "minilibx_macos/mlx.h"
#include "get_next_line/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"

#define WHITE_PIX 0xFFFFFF
#define MAP_WIDTH 150 * 2
#define MAP_HEIGHT 150 * 2
#define PIXEL_DISTANCE 50

typedef struct t_map
{
    int **matrix;
    int points_width;
    int points_height;
}               s_fdf;

void    fill_map(s_fdf *map, char *file_n);
int     count_lines(char *file_n);
int     count_nums(char *file_n);
