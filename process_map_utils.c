/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:45:36 by jpluta            #+#    #+#             */
/*   Updated: 2025/03/16 15:50:00 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_width_height_colour(t_fdf *map, char *file_n)
{
	map->points_height = count_lines(file_n);
	map->points_width = count_nums(file_n);
}

int	count_nums(char *file_n)
{
	int		num_count;
	char	*str;
	char	**t_str;
	int		fd;
	int		i;

	num_count = 0;
	i = 0;
	fd = open(file_n, O_RDONLY);
	if (fd == -1)
		exit(1);
	str = get_next_line(fd);
	t_str = ft_split(str, ' ');
	while (t_str[i])
	{
		if (*t_str[i] != ' ')
			num_count++;
		free(t_str[i++]);
	}
	free(t_str);
	free(str);
	close(fd);
	return (num_count);
}

int	count_lines(char *file_n)
{
	int		line_count;
	char	*str;
	int		fd;

	line_count = 0;
	fd = open(file_n, O_RDONLY);
	if (fd == -1)
		exit(1);
	str = get_next_line(fd);
	while (str)
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
