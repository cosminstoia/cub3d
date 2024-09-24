/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:56 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/23 18:16:55 by gstronge         ###   ########.fr       */
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
		check_map(cub3d);
		// -------------  PRINT MAP ----------------- //
		int i = 0;
		while(i < cub3d->map->height)
		{
			printf("%s\n", cub3d->map->m_arr[i]);
			i++;
		}
		// -------------  PRINT MAP ----------------- //
		cub3d->mlx = mlx_init(WNDW_WIDTH, WNDW_HEIGHT, "Cub3D", false);
		cub3d->main_img = mlx_new_image(cub3d->mlx, WNDW_WIDTH, WNDW_HEIGHT);
		mlx_image_to_window(cub3d->mlx, cub3d->main_img, 0, 0);
		cub3d->map_img = mlx_new_image(cub3d->mlx, 700, 700);
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
