/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jozefpluta <jozefpluta@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:26:58 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/12 18:54:30 by jozefpluta       ###   ########.fr       */
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

void    alloc_colour_matrix(s_fdf *map)
{
    // int     fd;
    int     i;
    // char    *str;
    // int     z;

    i = 0;
    map->colour_matrix = (int **)malloc(sizeof(int *) * (map->points_height + 1));
    while (i < map->points_height)
        map->colour_matrix[i++] = (int *)malloc(sizeof(int) * (map->points_width + 1));
    // str = get_next_line(fd);
    // i = 0;
    // while (map->points_height > i)
    // {
    //     z = 0;
    //     while (map->points_width > z)
    //         map->colour_matrix[i][z++] = 0; 
    //     i++;
    // }
    map->colour_matrix[i] = NULL;
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
    alloc_colour_matrix(map);
    str = get_next_line(fd);
    i = 0;
    while (map->points_height > i)
    {
        fill_data(map->matrix[i], map->colour_matrix[i], str);
        i++;
        free(str);
        str = get_next_line(fd);
    }
    map->matrix[i] = NULL;
    // map->colour_matrix[i] = NULL;
    close(fd);
}

int hex_to_int(const char *hex_str)
{
    int result = 0;

    // Skip the "0x" prefix
    if (hex_str[0] == '0' && hex_str[1] == 'x') {
        hex_str += 2; // Move past "0x"
    }

    // Iterate through the string and convert each character
    for (int i = 0; hex_str[i] != '\0'; i++) {
        result *= 16; // Shift the current result to the left (multiply by 16)
        
        char c = hex_str[i];
        int digit_value;

        // Convert hex character to its integer value
        if (c >= '0' && c <= '9') {
            digit_value = c - '0';  // '0' to '9' -> 0 to 9
        } else if (c >= 'a' && c <= 'f') {
            digit_value = c - 'a' + 10;  // 'a' to 'f' -> 10 to 15
        } else if (c >= 'A' && c <= 'F') {
            digit_value = c - 'A' + 10;  // 'A' to 'F' -> 10 to 15
        } else {
            // Invalid character (not a valid hex digit)
            break;
        }

        // Add the current digit's value to the result
        result += digit_value;
    }

    return result;
}

void    fill_data(int *line, int *colour_line, char *str)
{
    char    **temp_line;
    char    **temp_colour_line;
    char    *s;
    int     i;

    temp_line = ft_split(str, ' ');
    i = 0;
    while (temp_line[i])
    {
        s = NULL;
        s = ft_strchr(temp_line[i], ',');
        if (s)
        {
            temp_colour_line = ft_split(temp_line[i], ',');
            line[i] = ft_atoi(temp_colour_line[0]);
            // colour_line[i] = *temp_colour_line[1];
            colour_line[i] = hex_to_int(temp_colour_line[1]);
            free(temp_colour_line[0]);
            free(temp_colour_line[1]);
            free(temp_colour_line);
        }
        else
        {
            line[i] = ft_atoi(temp_line[i]);
            colour_line[i] = 0;
        }
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

