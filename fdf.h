#include "minilibx-linux/mlx.h"
#include "get_next_line/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include <math.h>

#define WHITE_PIX 16777215
#define SECOND_COLOUR 0x0000FF
#define MAP_WIDTH 1280
#define MAP_HEIGHT 760
#define POINT_DISTANCE 30

typedef struct t_fdf
{
    void    *mlx_image;
    int     **matrix;
    int     **colour_matrix;
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
void    alloc_colour_matrix(s_fdf *map);
void    fill_data(int *line, int *colour_line, char *str);
float   is_negat(float n);
float   is_greater(float x, float y);
void    bersenham(float x, float y, float x1, float y1, s_fdf *map);
void    print_map(s_fdf *map);
void    incrs_poin_dist(float *x, float *y, float *x1, float *y1);
void    isometric(float *x, float *y, int z, s_fdf *map);
void    padding(float *x, float *y, s_fdf *map);
int     hex_to_int(const char *hex_str);
int     get_inpt(int key, s_fdf *map);
void    free_all(s_fdf *map);
void    free_matrixes(s_fdf *map);
int     close_window(s_fdf *map);
void    free_temp_colour_line(char **temp_colour_line);
