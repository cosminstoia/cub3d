/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:56 by gstronge          #+#    #+#             */
/*   Updated: 2024/10/02 13:59:48 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_cub3d	*ft_make_structs(t_cub3d *cub3d)
{
	t_map		*map;
	t_player	*player;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		free(cub3d);
		return (NULL);
	}
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
	{
		free(cub3d);
		free(map);
		return (NULL);
	}
	cub3d->map = map;
	cub3d->player = player;
	return (cub3d);
}

int	ft_load_textures(t_cub3d *cub3d)
{
	cub3d->texture_array[0] = mlx_load_png(cub3d->map->no);
	cub3d->texture_array[1] = mlx_load_png(cub3d->map->so);
	cub3d->texture_array[2] = mlx_load_png(cub3d->map->we);
	cub3d->texture_array[3] = mlx_load_png(cub3d->map->ea);
	if (cub3d->texture_array[0] == NULL || cub3d->texture_array[1] == NULL \
		|| cub3d->texture_array[2] == NULL || cub3d->texture_array[3] == NULL)
	{
		printf("error loading texture images\n");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub3d		*cub3d;

	if (argc != 2)
	{
		printf("Error:\nInvalid number of arguments");
		// ft_cleanup(cub3d);ß
		exit(EXIT_FAILURE);
	}
	cub3d = NULL;
	cub3d = ft_make_structs(cub3d);
	if (!cub3d)
		return (1);
	ft_read_input(argv[1], cub3d->map);
	ft_check_input(cub3d, argv[1]);
	cub3d->mlx = mlx_init(WNDW_WIDTH, WNDW_HEIGHT, "Cub3D", true);
	ft_load_textures(cub3d);
	cub3d->main_img = mlx_new_image(cub3d->mlx, WNDW_WIDTH, WNDW_HEIGHT);
	mlx_image_to_window(cub3d->mlx, cub3d->main_img, 0, 0);
	cub3d->map_img = mlx_new_image(cub3d->mlx, MAP_SIZE, MAP_SIZE);
	mlx_image_to_window(cub3d->mlx, cub3d->map_img, 0, 0);
	ft_draw_player(cub3d, cub3d->player, cub3d->map->scale);
	mlx_loop_hook(cub3d->mlx, ft_move_player, cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
	// ft_cleanup(cub3d);
	return (EXIT_SUCCESS);
}
