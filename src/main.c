/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:56 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/28 15:25:09 by cstoia           ###   ########.fr       */
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
	printf("%s", cub3d->map->no);
	cub3d->texture_array[0] = mlx_load_png(cub3d->map->no);
	cub3d->texture_array[1] = mlx_load_png(cub3d->map->so);
	cub3d->texture_array[2] = mlx_load_png(cub3d->map->we);
	cub3d->texture_array[3] = mlx_load_png(cub3d->map->ea);
	if (cub3d->texture_array[0] == NULL || cub3d->texture_array[1] == NULL || cub3d->texture_array[2] == NULL || cub3d->texture_array[3] == NULL)
		return (-1);
	return (0);
}

int main(int argc, char **argv)
{
	t_cub3d		*cub3d;
	
	if(argc == 2)
	{
		cub3d = NULL;
		cub3d = ft_make_structs(cub3d);
		if (!cub3d)
			return (1);
		read_input(argv[1], cub3d->map);
		check_input(cub3d, argv[1]);
		cub3d->mlx = mlx_init(WNDW_WIDTH, WNDW_HEIGHT, "Cub3D", false);
		ft_load_textures(cub3d);
		cub3d->main_img = mlx_new_image(cub3d->mlx, WNDW_WIDTH, WNDW_HEIGHT);
		mlx_image_to_window(cub3d->mlx, cub3d->main_img, 0, 0);
		// // -------------  PRINT MAP ----------------- //
		// int i = 0;
		// while(i < cub3d->map->height)
		// {
		// 	printf("%s\n", cub3d->map->mapcopy[i]);
		// 	i++;
		// }
		//printf("North Texture: %s\n", cub3d->map->no);
		// printf("South Texture: %s\n", cub3d->map->so);
		// printf("East Texture: %s\n", cub3d->map->ea);
		// printf("West Texture: %s\n", cub3d->map->we);
		// printf("Floor Color r g b: %d, %d, %d\n", cub3d->map->floor[0], cub3d->map->floor[1], cub3d->map->floor[2]);
		// printf("Ceiling Color r g b: %d, %d, %d\n", cub3d->map->ceiling[0], cub3d->map->ceiling[1], cub3d->map->ceiling[2]);
		// printf("Floor Color (Hex): %#06lx\n", cub3d->map->hex_flr);
		// printf("Ceiling Color (Hex): %#06lx\n", cub3d->map->hex_clg);
		// printf("Floor Color (dev): %lu\n", cub3d->map->hex_flr);
		// printf("Ceiling Color (dec): %lu\n", cub3d->map->hex_clg);
		// printf("Map Width: %d\n", cub3d->map->width);
		// printf("Map Height: %d\n", cub3d->map->height);
		// // -------------  PRINT MAP ----------------- //
		cub3d->map_img = mlx_new_image(cub3d->mlx, MAP_SIZE, MAP_SIZE);
		mlx_image_to_window(cub3d->mlx, cub3d->map_img, 20, 20);
		ft_draw_player(cub3d, cub3d->player, cub3d->map->scale);
		mlx_loop_hook(cub3d->mlx, ft_move_player, cub3d);
		mlx_loop(cub3d->mlx);
		mlx_terminate(cub3d->mlx);
		// ft_cleanup(cub3d);
	}
	else
	{
		printf("Error:\nInvalid number of arguments");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
