/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:56 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/25 11:38:24 by cstoia           ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_cub3d		*cub3d;
	
	if(argc == 2)
	{
		cub3d = NULL;
		cub3d = ft_make_structs(cub3d);
		if (!cub3d)
			return (1);
		read_map(argv[1], cub3d->map);
		check_map(cub3d, argv[1]);
		cub3d->mlx = mlx_init(WNDW_WIDTH, WNDW_HEIGHT, "Cub3D", false);
		cub3d->main_img = mlx_new_image(cub3d->mlx, WNDW_WIDTH, WNDW_HEIGHT);
		mlx_image_to_window(cub3d->mlx, cub3d->main_img, 0, 0);
		// // -------------  PRINT MAP ----------------- //
		// int i = 0;
		// while(i < cub3d->map->height)
		// {
		// 	printf("%s\n", cub3d->map->m_arr[i]);
		// 	i++;
		// }
		// printf("North Texture: %s\n", cub3d->map->NO);
		// printf("South Texture: %s\n", cub3d->map->SO);
		// printf("East Texture: %s\n", cub3d->map->EA);
		// printf("West Texture: %s\n", cub3d->map->WE);
		// printf("Floor Color (Hex): %#06lx\n", cub3d->map->hex_F);
		// printf("Ceiling Color (Hex): %#06lx\n", cub3d->map->hex_C);
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
