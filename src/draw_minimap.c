/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:18:25 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/21 14:49:53 by gstronge         ###   ########.fr       */
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
	float vert_len;
	// float horiz_len;

	vert_len = 0;
	vert_len = ft_ray_vert(cub3d, player, vert_len, scale);

	// horiz_len = 0;
	// horiz_len = ft_ray_horiz(cub3d, cub3d->player, vert_len, scale);
	// if (vert_len > horiz_len)

}

float	ft_ray_vert(t_cub3d *cub3d, t_player *player, float vert_len, int scale)
{
	float	dx;
	float	dy;
	float	end_x;
	float	end_y;
	float	step;
	if (player->angle < 1.5 * PI && player->angle > 0.5 * PI)
	{
		end_x = floor(player->pos_x) - 0.001;
		dx = end_x - player->pos_x;
		step = -1;
	}
	else
	{
		end_x = ceil(player->pos_x) + 0.001;
		dx = end_x - player->pos_x;
		step = 1;
	}
	
	dy = tan(player->angle) * dx;
	end_y = player->pos_y + dy;

	while (end_x >= 0 && end_x <= cub3d->map->width && end_y >= 0 && end_y <= cub3d->map->height && cub3d->map->m_arr[(int)(end_y)][(int)end_x] != 1)
	{
		// printf(" angle = %f, end_x = %f, end_y = %f, dx = %f, dy = %f\n", player->angle, end_x, end_y, dx, dy);
		dx += step;
		end_x += step;
		dy = tan(player->angle) * dx;
		end_y = player->pos_y + dy;
	}
	
	if (step == -1)
	{
		dx += 0.002;
		end_x += 0.002;
	}
	else
	{
		dx -= 0.002;
		end_x -= 0.002;
	}
	dy = tan(player->angle) * dx;
	end_y = player->pos_y + dy;
	
	if (end_x >= 0 && end_x <= cub3d->map->width && end_y >= 0 && end_y <= cub3d->map->height)
	{		
		mlx_put_pixel(cub3d->map_img, (end_x * scale), (end_y * scale), 0xFFFF00FF);
		mlx_put_pixel(cub3d->map_img, (end_x * scale) + 1, (end_y * scale), 0xFFFF00FF);
		mlx_put_pixel(cub3d->map_img, (end_x * scale) + 1, (end_y * scale) + 1, 0xFFFF00FF);
		mlx_put_pixel(cub3d->map_img, (end_x * scale), (end_y * scale) + 1, 0xFFFF00FF);
	}
	ft_draw_line(cub3d, player->pos_x * scale, player->pos_y * scale, end_x * scale, end_y * scale);
	vert_len = dx / cos(player->angle);
	return (vert_len);
}
