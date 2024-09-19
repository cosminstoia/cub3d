/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:18:25 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/19 16:19:41 by gstronge         ###   ########.fr       */
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
				ft_print_block(cub3d, arr_x, arr_y, 0xFFFFFFFF);
			else
				ft_print_block(cub3d, arr_x, arr_y, 0x000000FF);
			arr_x++;
		}
		arr_y++;
	}
}

void	ft_print_block(t_cub3d *cub3d, int arr_x, int arr_y, u_int32_t colour)
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

void	ft_draw_player(t_cub3d *cub3d, t_player *player, int scale)
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

void	ft_draw_ray(t_cub3d *cub3d, t_player *player, int scale)
{
	float	first_dx;
	float	first_dy;
	float	first_x;
	float	first_y;

	if (player->angle < 1.5 * PI && player->angle > 0.5 * PI)
	{
		first_x = floor(player->pos_x);
		first_dx = first_x - player->pos_x;
	}
	else
	{
		first_x = ceil(player->pos_x);
		first_dx = player->pos_x - first_x;
	}
	
	first_dy = -tan(player->angle) * first_dx;
	if (player->angle < 1.5 * PI && player->angle > 0.5 * PI)
		first_dy *= -1;
	first_y = player->pos_y + first_dy;
	
	printf("           first_x = %f, first_y = %f\n", first_x, first_y);

	if (first_x >= 0 && first_x < cub3d->map->width && first_y >= 0 && first_y < cub3d->map->height)
	{		
		mlx_put_pixel(cub3d->map_img, (first_x * scale), (first_y * scale), 0xFFFF00FF);
		mlx_put_pixel(cub3d->map_img, (first_x * scale) + 1, (first_y * scale), 0xFFFF00FF);
		mlx_put_pixel(cub3d->map_img, (first_x * scale) + 1, (first_y * scale) + 1, 0xFFFF00FF);
		mlx_put_pixel(cub3d->map_img, (first_x * scale), (first_y * scale) + 1, 0xFFFF00FF);
	}
	ft_draw_line(cub3d, player->pos_x * scale, player->pos_y * scale, first_x * scale, first_y * scale);

}
