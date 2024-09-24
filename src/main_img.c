/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:07:05 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/23 18:16:55 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_main_img(t_cub3d *cub3d, t_ray ray, float orig_angle, int x)
{
	double	wall_height;
	int		x_adj;
	int		wall_pix;
	int		y;
	double	distance;
	double	angle_diff;
	
	angle_diff = orig_angle - cub3d->player->angle;
	if (angle_diff < 0)
		angle_diff += 2 * PI; 
	if (angle_diff > 2 * PI)
		angle_diff -= 2 * PI; 
	distance = ray.len * cos(angle_diff);
	x_adj = x;
	while (x_adj < x + 5)
	{
		y = 0;
		while (y < (WNDW_HEIGHT / 2))
		{
			mlx_put_pixel(cub3d->main_img, x_adj, y, 0x003300FF);
			y++;
		}
		while (y < WNDW_HEIGHT)
		{
			mlx_put_pixel(cub3d->main_img, x_adj, y, 0x330000FF);
			y++;
		}
		x_adj++;
	}
	x_adj = x;
	wall_height = (1 * WNDW_HEIGHT) / distance;
	while (x_adj < x + 5)
	{
		y = 0;
		wall_pix = (WNDW_HEIGHT / 2) - (wall_height / 2);
		if (wall_pix < 0)
			wall_pix = 0;
		while (y < wall_height && y < WNDW_HEIGHT)
		{
			mlx_put_pixel(cub3d->main_img, x_adj, y + wall_pix, 0x0000FFFF);
			y++;
		}
		x_adj++;
	}
}
