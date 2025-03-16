/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:26:58 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/16 15:50:18 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	alloc_colour_matrix(t_fdf *map)
{
	int	i;

	i = 0;
	map->colour_matrix = (int **)malloc(sizeof(int *)
			* (map->points_height + 1));
	while (i < map->points_height)
	{
		map->colour_matrix[i] = (int *)malloc(sizeof(int)
				* (map->points_width + 1));
		i++;
	}
}

void	alloc_matrix(t_fdf *map, char *file_n)
{
	int		fd;
	int		i;
	char	*str;

	fd = open(file_n, O_RDONLY);
	i = 0;
	map->matrix = (int **)malloc(sizeof(int *) * (map->points_height + 1));
	while (i < map->points_height)
		map->matrix[i++] = (int *)malloc(sizeof(int) * (map->points_width + 1));
	alloc_colour_matrix(map);
	str = get_next_line(fd);
	i = 0;
	while (i < map->points_height)
	{
		fill_data(map->matrix[i], map->colour_matrix[i], str);
		i++;
		free(str);
		str = NULL;
		str = get_next_line(fd);
	}
	if (str)
		free(str);
	map->matrix[i] = NULL;
	map->colour_matrix[i] = NULL;
	close(fd);
}

int	hex_to_int(const char *hex_str)
{
	int		result;
	int		i;
	char	c;
	int		digit_value;

	result = 0;
	i = 0;
	digit_value = 0;
	if (hex_str[0] == '0' && hex_str[1] == 'x')
		hex_str += 2;
	while (hex_str[i] != '\0')
	{
		result *= 16;
		c = hex_str[i++];
		if (c >= '0' && c <= '9')
			digit_value = c - '0';
		else if (c >= 'a' && c <= 'f')
			digit_value = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			digit_value = c - 'A' + 10;
		else
			break ;
		result += digit_value;
	}
	return (result);
}

void	fill_data(int *line, int *colour_line, char *str)
{
	char	**temp_line;
	char	**temp_colour_line;
	char	*s;
	int		i;

	temp_line = ft_split(str, ' ');
	i = 0;
	while (temp_line[i])
	{
		s = ft_strchr(temp_line[i], ',');
		if (s)
		{
			temp_colour_line = ft_split(temp_line[i], ',');
			line[i] = ft_atoi(temp_colour_line[0]);
			colour_line[i] = hex_to_int(temp_colour_line[1]);
			free_temp_colour_line(temp_colour_line);
		}
		else
		{
			line[i] = ft_atoi(temp_line[i]);
			colour_line[i] = 0;
		}
		free(temp_line[i++]);
	}
	free(temp_line);
}
