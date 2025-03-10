/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:26:58 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/10 16:46:44 by jozefpluta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    get_width_height(s_fdf *map, char *file_n)
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

void    alloc_matrix(s_fdf *map, char *file_n)
{
    int     fd;
    int     i;
    char    *str;

    fd = open(file_n, O_RDONLY);
    i = 0;
    if (fd == -1)
        exit(1);
    map->matrix = (int **)malloc(sizeof(int *) * (map->points_height + 1));
    while (i < map->points_height)
        map->matrix[i++] = (int *)malloc(sizeof(int) * (map->points_width + 1));
    str = get_next_line(fd);
    i = 0;
    while (map->points_height > i)
    {
        fill_data(map->matrix[i++], str);
        free(str);
        str = get_next_line(fd);
    }
    map->matrix[i] = NULL;
    close(fd);
}

void    fill_data(int *line, char *str)
{
    char **temp_line;
    int i;

    temp_line = ft_split(str, ' ');
    i = 0;
    while (temp_line[i])
    {
        line[i] = ft_atoi(temp_line[i]);
        free(temp_line[i]);
        i++;
    }
    free(temp_line);
}

// 1,0xff 
// 0,0xff 
// 1,0xff 
// 1,0xff 
// 0,0xff

