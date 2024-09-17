/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:56 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/16 19:09:11 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_move_player(void* param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;

	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		cub3d->player->instances[0].y -= 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		cub3d->player->instances[0].y += 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		cub3d->player->instances[0].x -= 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		cub3d->player->instances[0].x += 5;
}

void ft_make_player(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			mlx_put_pixel(cub3d->player, x, y, 42424242);
			y++;
		}
		x++;		
	}
}

int TEMP_copy_map_array(t_map *map)
{
	int row0[] = {1,1,1,1,1,1,1};
	int row1[] = {1,0,1,0,0,0,1};
	int row2[] = {1,0,1,1,0,0,1};
	int row3[] = {1,0,0,0,0,0,1};
	int row4[] = {1,0,0,0,0,2,1};
	int row5[] = {1,1,1,1,1,1,1};

	memcpy(map->map_arr[0], row0, sizeof(row0));
	memcpy(map->map_arr[1], row1, sizeof(row1));
	memcpy(map->map_arr[2], row2, sizeof(row2));
	memcpy(map->map_arr[3], row3, sizeof(row3));
	memcpy(map->map_arr[4], row4, sizeof(row4));
	memcpy(map->map_arr[5], row5, sizeof(row5));
	return (0);
}

int	make_map(t_map *map)
{
	int i;

	i = 0;
	map->scale = 100;//TEMP: need to figure out a way to scale it correctly to fit in the top corner
	map->width = 7;//TEMP: need to calculate this from the parsing
	map->height = 6;//TEMP: need to calculate this from the parsing
	map->player_x = 5;//TEMP: need to calculate this from the parsing
	map->player_y = 4;//TEMP: need to calculate this from the parsing
	map->map_arr = malloc(map->height * sizeof(int *));
	if (!map->map_arr)
		return(-1);
	while (i < map->height)
	{
		map->map_arr[i] = malloc(map->width * sizeof(int));
		if (!map->map_arr[i])
			return(-1);
		i++;
	}

	TEMP_copy_map_array(map);//TEMP: temp function so ray casting can be done with test map before parsing is done correctly

	return (0);
}

void ft_print_block(t_cub3d *cub3d, t_map *map, int arr_x, int arr_y)
{
	int	x;
	int	y;
	int	x_start;
	int	y_start;

	y = 0;
	x_start = map->scale * arr_x;
	y_start = map->scale * arr_y;
	while (y < map->scale)
	{		
		x = 0;
		while (x < map->scale)
		{
			mlx_put_pixel(cub3d->mini_map, x_start + x, y_start + y, 848484);
			x++;
		}
		y++;
	}
}

void	ft_draw_map(t_cub3d *cub3d, t_map *map)
{
	int	arr_x;
	int	arr_y;

	arr_y = 0;

	while (arr_y < map->height)
	{
		arr_x = 0;
		while (arr_x < map->width)
		{
			if (map->map_arr[arr_y][arr_x] == 1)
			{

				ft_print_block(cub3d, map, arr_x, arr_y);
			}
			arr_x++;
		}
		arr_y++;
	}
}

int main(void)
{
	t_cub3d		*cub3d;
	t_map		*map;
	
	cub3d = NULL;
	map = NULL;
	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	cub3d->mlx = mlx_init(1000, 1000, "Cub3D", false);
	cub3d->player = mlx_new_image(cub3d->mlx, 5, 5);
	cub3d->mini_map = mlx_new_image(cub3d->mlx, 700, 700);
	mlx_image_to_window(cub3d->mlx, cub3d->mini_map, 50, 50);
	ft_make_player(cub3d);
	make_map(map);
	ft_draw_map(cub3d, map);
	mlx_image_to_window(cub3d->mlx, cub3d->player, (map->player_x * map->scale) + 50, (map->player_y * map->scale) + 50);

	mlx_loop_hook(cub3d->mlx, ft_move_player, cub3d);
	mlx_loop(cub3d->mlx);

	mlx_terminate(cub3d->mlx);
    free(cub3d);
    free(map);
	return (0);
}