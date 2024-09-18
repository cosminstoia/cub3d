/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:18:25 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/18 11:21:18 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
			if (map->m_arr[arr_y][arr_x] == 1)
			{
				ft_print_block(cub3d, arr_x, arr_y, 0xFFFFFFFF);
			}
			else
				ft_print_block(cub3d, arr_x, arr_y, 0x000000FF);
			arr_x++;
		}
		arr_y++;
	}
}

void ft_print_block(t_cub3d *cub3d, int arr_x, int arr_y, u_int32_t colour)
{
	int	x;
	int	y;
	int	x_start;
	int	y_start;

	y = 0;
	x_start = cub3d->map->scale * arr_x;
	y_start = cub3d->map->scale * arr_y;
	while (y < cub3d->map->scale)
	{		
		x = 0;
		while (x < cub3d->map->scale)
		{
			mlx_put_pixel(cub3d->map_img, x_start + x, y_start + y, colour);
			x++;
		}
		y++;
	}
}

void ft_draw_player(t_cub3d *cub3d, t_player *player, int scale)
{
	ft_draw_map(cub3d, cub3d->map);
	int	x;
	int	y;

	x = 0;
	while (x < 4)
	{
		y = 0;
		while (y < 4)
		{
			mlx_put_pixel(cub3d->map_img, x + (player->pos_x * scale) -2, y + (player->pos_y * scale) -2, 0x00FF00FF);
			y++;
		}
		x++;		
	}
}
