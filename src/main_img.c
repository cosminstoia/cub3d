/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:07:05 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/26 18:19:49 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	ft_wall_pix_clr(t_ray ray, double wall_height, int y)
{

	uint32_t		colour;
	int	index;
	float			x;
	int				offset;

	offset = 0;
	if (ray.is_north_or_south)
		x = round(ray.texture->width * (ray.end_x - floor(ray.end_x)));
	else
		x = round(ray.texture->width * (ray.end_y - floor(ray.end_y)));

	// printf("here in NORTH SOUTH\n");
	if (wall_height > WNDW_HEIGHT)
		offset = (((wall_height - WNDW_HEIGHT) / 2) / wall_height) * ray.texture->height;
	y = (round((ray.texture->height / wall_height) * y)) + offset;

	index = (x + (y * ray.texture->height)) * 4;
	if (index < 0)
			printf("index %d\n", index);
	if ((uint32_t)y <= ray.texture->height && (uint32_t)x <= ray.texture->width)
		colour =  (ray.texture->pixels[index] << 24) | (ray.texture->pixels[index + 1] << 16) | (ray.texture->pixels[index + 2] << 8) | ray.texture->pixels[index + 3];
	else
		colour = 0;
	return (colour);
}

void	ft_draw_main_img(t_cub3d *cub3d, t_ray ray, float orig_angle, int x)
{
	double		wall_height;
	int			x_adj;
	int			wall_pix;
	int			y;
	double		distance;
	uint32_t	colour;

	y = 0;
	x_adj = x;
	ft_draw_clg_and_flr(cub3d, x_adj, x, y);
	distance = ft_correct_fisheye(cub3d, ray, orig_angle);
	wall_height = (1 * WNDW_HEIGHT) / distance;


	while (x_adj < x + 5)
	{
		y = 0;
		wall_pix = round((WNDW_HEIGHT / 2) - (wall_height / 2));
		if (wall_pix < 0)
			wall_pix = 0;
		while (y <= wall_height && y <= WNDW_HEIGHT)
		{
			colour = ft_wall_pix_clr(ray, wall_height, y);

			mlx_put_pixel(cub3d->main_img, x_adj, y + wall_pix, colour);
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
