/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:56 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/18 11:27:46 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int TEMP_copy_map_array(t_map *map)
{
	int row0[] = {1,1,1,1,1,1,1};
	int row1[] = {1,0,1,0,0,0,1};
	int row2[] = {1,0,1,1,0,0,1};
	int row3[] = {1,0,0,0,0,0,1};
	int row4[] = {1,0,0,0,0,2,1};
	int row5[] = {1,1,1,1,1,1,1};

	memcpy(map->m_arr[0], row0, sizeof(row0));
	memcpy(map->m_arr[1], row1, sizeof(row1));
	memcpy(map->m_arr[2], row2, sizeof(row2));
	memcpy(map->m_arr[3], row3, sizeof(row3));
	memcpy(map->m_arr[4], row4, sizeof(row4));
	memcpy(map->m_arr[5], row5, sizeof(row5));
	return (0);
}

int	make_map(t_map *map)
{
	int i;

	i = 0;
	map->scale = 100;//TEMP: need to figure out a way to scale it correctly to fit in the top corner
	map->width = 7;//TEMP: need to calculate this from the parsing
	map->height = 6;//TEMP: need to calculate this from the parsing
	map->m_arr = malloc(map->height * sizeof(int *));
	if (!map->m_arr)
		return(-1);
	while (i < map->height)
	{
		map->m_arr[i] = malloc(map->width * sizeof(int));
		if (!map->m_arr[i])
			return(-1);
		i++;
	}

	TEMP_copy_map_array(map);//TEMP: temp function so ray casting can be done with test map before parsing is done correctly

	return (0);
}


void ft_make_player(t_cub3d *cub3d, t_player *player, int scale)
{
	player->pos_x = 5;//TEMP: need to calculate this from the parsing
	player->pos_y = 4;//TEMP: need to calculate this from the parsing
	player->dx = 0;//TEMP: need to calculate this from the parsing
	player->dy = -0.05;//TEMP: assumes facing north need to calculate this from the parsing
	player->p_angle = PI * 1.5;//TEMP: need to calculate this from the parsing (1.5 * PI is north)
	ft_draw_player(cub3d, player, scale);
}

t_cub3d	*ft_make_structs(t_cub3d *cub3d)
{
	t_map		*map;
	t_player	*player;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
	{
		free(cub3d);
		return (NULL);
	}
	player = malloc(sizeof(t_player));
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

int main(void)
{
	t_cub3d		*cub3d;
	
	cub3d = NULL;
	cub3d = ft_make_structs(cub3d);
	if (!cub3d)
		return (1);
	cub3d->mlx = mlx_init(2500, 1500, "Cub3D", false);
	cub3d->map_img = mlx_new_image(cub3d->mlx, 700, 700);
	mlx_image_to_window(cub3d->mlx, cub3d->map_img, 20, 20);
	make_map(cub3d->map);
	ft_make_player(cub3d, cub3d->player, cub3d->map->scale);
	ft_draw_map(cub3d, cub3d->map);

	mlx_loop_hook(cub3d->mlx, ft_move_player, cub3d);
	mlx_loop(cub3d->mlx);

	mlx_terminate(cub3d->mlx);
    // ft_cleanup(cub3d);
	return (0);
}
