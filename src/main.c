/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:56 by gstronge          #+#    #+#             */
/*   Updated: 2024/10/04 17:29:29 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_cub3d	*ft_make_structs(t_cub3d *cub3d)
{
	t_map		*map;
	t_player	*player;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		ft_cleanup(cub3d, "Error\nmalloc failed\n", EXIT_FAILURE);
	cub3d->texture_array[0] = NULL;
	cub3d->texture_array[1] = NULL;
	cub3d->texture_array[2] = NULL;
	cub3d->texture_array[3] = NULL;
	cub3d->mlx = NULL;
	cub3d->map_img = NULL;
	cub3d->main_img = NULL;
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		ft_cleanup(cub3d, "Error\nmalloc failed\n", EXIT_FAILURE);
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		ft_cleanup(cub3d, "Error\nmalloc failed\n", EXIT_FAILURE);
	cub3d->map = map;
	cub3d->player = player;
	return (cub3d);
}

void	ft_load_textures(t_cub3d *cub3d)
{
	cub3d->texture_array[0] = mlx_load_png(cub3d->map->no);
	if (!cub3d->texture_array[0])
		ft_cleanup(cub3d, "Error\ntexture couldn't be loaded\n", EXIT_FAILURE);
	cub3d->texture_array[1] = mlx_load_png(cub3d->map->so);
	if (!cub3d->texture_array[1])
		ft_cleanup(cub3d, "Error\ntexture couldn't be loaded\n", EXIT_FAILURE);
	cub3d->texture_array[2] = mlx_load_png(cub3d->map->we);
	if (!cub3d->texture_array[2])
		ft_cleanup(cub3d, "Error\ntexture couldn't be loaded\n", EXIT_FAILURE);
	cub3d->texture_array[3] = mlx_load_png(cub3d->map->ea);
	if (!cub3d->texture_array[3])
		ft_cleanup(cub3d, "Error\ntexture couldn't be loaded\n", EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	cub3d = NULL;
	if (argc != 2)
		ft_cleanup(cub3d, "Error\nInvalid number of arguments\n", EXIT_FAILURE);
	cub3d = ft_make_structs(cub3d);
	ft_read_input(cub3d, argv[1], cub3d->map);
	ft_check_input(cub3d, argv[1]);
	ft_load_textures(cub3d);
	cub3d->mlx = mlx_init(WNDW_WIDTH, WNDW_HEIGHT, "Cub3D", true);
	if (cub3d->mlx == NULL)
		ft_cleanup(cub3d, "Error\nmlx library failure\n", EXIT_FAILURE);
	cub3d->main_img = mlx_new_image(cub3d->mlx, WNDW_WIDTH, WNDW_HEIGHT);
	if (cub3d->main_img == NULL)
		ft_cleanup(cub3d, "Error\nmlx library failure\n", EXIT_FAILURE);
	mlx_image_to_window(cub3d->mlx, cub3d->main_img, 0, 0);
	cub3d->map_img = mlx_new_image(cub3d->mlx, MAP_SIZE, MAP_SIZE);
	if (cub3d->map_img == NULL)
		ft_cleanup(cub3d, "Error\nmlx library failure\n", EXIT_FAILURE);
	mlx_image_to_window(cub3d->mlx, cub3d->map_img, 0, 0);
	ft_draw_player(cub3d, cub3d->player, cub3d->map->scale);
	mlx_loop_hook(cub3d->mlx, ft_move_player, cub3d);
	mlx_loop(cub3d->mlx);
	ft_cleanup(cub3d, NULL, EXIT_SUCCESS);
}
