#include "minilibx-linux/mlx.h"
#include "libft/get_next_line/get_next_line.h"
#include "libft/ft_printf/ft_printf.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include <math.h>
#include <X11/keysym.h>

#define WHITE_PIX 16777215
#define SECOND_COLOUR 0x0000FF
#define MAP_WIDTH 1980 //1280
#define MAP_HEIGHT 1200 //760
#define POINT_DISTANCE 23

typedef struct t_fdf
{
    void    *mlx_image;
    char    *mlx_img_data;
    int     bpp;
    int     size_line;
    int     endian;
    void    *mlx_connection;
    void    *mlx_window;
    int     **matrix;
    int     **colour_matrix;
    int     points_width;
    int     points_height;
    int     colour;
}                       s_fdf;

void    get_mlx_data(s_fdf *map, char *name);
void    edge_cases(int argc, char *argv);
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
void    my_put_pixel(float *x, float *y, float x_dest, float y_dest, s_fdf *map);
