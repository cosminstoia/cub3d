/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:07:05 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/24 19:43:14 by gstronge         ###   ########.fr       */
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

	y = 0;
	x_adj = x;
	ft_draw_clg_and_flr(cub3d, x_adj, x, y);
	distance = ft_correct_fisheye(cub3d, ray, orig_angle);
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

double	ft_correct_fisheye(t_cub3d *cub3d, t_ray ray, double orig_angle)
{
	double	distance;
	double	angle_diff;

	angle_diff = orig_angle - cub3d->player->angle;
	if (angle_diff < 0)
		angle_diff += 2 * PI;
	if (angle_diff > 2 * PI)
		angle_diff -= 2 * PI;
	distance = ray.len * cos(angle_diff);
	return (distance);
}

void	ft_draw_clg_and_flr(t_cub3d *cub3d, int x_adj, int x, int y)
{
	while (x_adj < x + 5)
	{
		y = 0;
		while (y < (WNDW_HEIGHT / 2))
		{
			mlx_put_pixel(cub3d->main_img, x_adj, y, cub3d->map->hex_clg);
			y++;
		}
		while (y < WNDW_HEIGHT)
		{
			mlx_put_pixel(cub3d->main_img, x_adj, y, cub3d->map->hex_flr);
			y++;
		}
		x_adj++;
	}
}
