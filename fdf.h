#include "minilibx_macos/mlx.h"
#include "get_next_line/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include <math.h>

#define WHITE_PIX 0xFFFFFF
#define MAP_WIDTH 150 * 2
#define MAP_HEIGHT 150 * 2
#define POINT_DISTANCE 30
#define ANGLE 30

typedef struct t_map
{
    int     **matrix;
    int     points_width;
    int     points_height;
    void    *mlx_connection;
    void    *mlx_window;
    int     colour;
}                       s_fdf;

void    get_width_height(s_fdf *map, char *file_n);
int     count_lines(char *file_n);
int     count_nums(char *file_n);
void    alloc_matrix(s_fdf *map, char *file_n);
void    fill_data(int *line, char *str);
float   is_negat(float n);
float   is_greater(float x, float y);
void    bersenham(float x, float y, float x1, float y1, s_fdf *map);
void    print_map(s_fdf *map);
void    incrs_poin_dist(float *x, float *y, float *x1, float *y1);
void    isometric(float *x, float *y, int z);
