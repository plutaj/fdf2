/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpluta <jpluta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:26:48 by jozefpluta        #+#    #+#             */
/*   Updated: 2025/03/16 15:59:25 by jpluta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*map;

	edge_cases(argc, argv[1]);
	map = (t_fdf *)malloc(sizeof(t_fdf));
	get_width_height_colour(map, argv[1]);
	alloc_matrix(map, argv[1]);
	map->true_colour = find_colour(map);
	get_mlx_data(map, argv[1]);
	print_map(map);
	mlx_put_image_to_window(map->mlx_connection, map->mlx_window,
		map->mlx_image, 0, 0);
	mlx_hook(map->mlx_window, 17, 0, close_window, map);
	mlx_key_hook(map->mlx_window, get_inpt, map);
	mlx_loop(map->mlx_connection);
	return (0);
}
