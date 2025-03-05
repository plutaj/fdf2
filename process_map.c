#include "fdf.h"

void    fill_map(s_fdf *map, char *file_n)
{
    map->points_height = count_lines(file_n);
    map->points_width = count_nums(file_n);
}

int count_nums(char *file_n)
{
    int     num_count;
    char    *str;
    char    *t_str;
    int     fd;

    num_count = 0;
    fd = open(file_n, O_RDONLY);
    if (fd == -1)
        exit(1);
    str = get_next_line(fd);
    t_str = str;
    while (*str)
    {
        if (*str != ' ')
        {
            num_count++;
            while(*str != ' ' && *str)
                str++;
        }
        while (*str == ' ')
            str++;
    }
    free(t_str);
    return (num_count);
}

int count_lines(char *file_n)
{
    int     line_count;
    char    *str;
    int     fd;

    line_count = 0;
    fd = open(file_n, O_RDONLY);
    if (fd == -1)
        exit(1);
    str = get_next_line(fd);
    while(str)
    {
        line_count++;
        free(str);
        str = get_next_line(fd);
    }
    if (str)
        free(str);
    close(fd);
    return (line_count);
}

