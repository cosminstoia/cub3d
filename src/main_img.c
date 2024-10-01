/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:07:05 by gstronge          #+#    #+#             */
/*   Updated: 2024/10/01 12:14:07 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	ft_wall_pix_clr(t_ray ray, float wall_height, uint32_t y)
{

	uint32_t		colour;
	unsigned int	index;
	uint32_t		x;
	int				offset;

	offset = 0;
	colour = 0;
	if (ray.is_north_or_south)
		x = round(ray.texture->width * (ray.end_x - floor(ray.end_x)));
	else
		x = round(ray.texture->width * (ray.end_y - floor(ray.end_y)));
	if (round(wall_height) > WNDW_HEIGHT)
		offset = round((((wall_height - WNDW_HEIGHT) / 2) / wall_height) * ray.texture->height);
	y = round((ray.texture->height / wall_height) * y) + offset;
	index = (x + (y * ray.texture->width)) * 4;

	if (y <= ray.texture->height && x <= ray.texture->width && index < ray.texture->width * ray.texture->height * 4)
		colour = (ray.texture->pixels[index] << 24) | (ray.texture->pixels[index + 1] << 16) | (ray.texture->pixels[index + 2] << 8) | ray.texture->pixels[index + 3];
	return (colour);
}

void	ft_draw_main_img(t_cub3d *cub3d, t_ray ray, float orig_angle, int x)
{
	float		wall_height;
	int			top_of_wall;
	uint32_t	y;
	double		distance;
	uint32_t	colour;

	y = 0;
	ft_draw_clg_and_flr(cub3d, x, y);
	distance = ft_correct_fisheye(cub3d, ray, orig_angle);
	wall_height = (1 * WNDW_HEIGHT) / distance;

	y = 0;
	top_of_wall = round((WNDW_HEIGHT / 2) - (wall_height / 2));
	if (top_of_wall < 0)
		top_of_wall = 0;
	while (y < floor(wall_height) && y < WNDW_HEIGHT)
	{
		colour = ft_wall_pix_clr(ray, wall_height, y);

		mlx_put_pixel(cub3d->main_img, x, y + top_of_wall, colour);
		y++;
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

void	ft_draw_clg_and_flr(t_cub3d *cub3d, int x, int y)
{
	y = 0;
	while (y < (WNDW_HEIGHT / 2))
	{
		mlx_put_pixel(cub3d->main_img, x, y, cub3d->map->hex_clg);
		y++;
	}
	while (y < WNDW_HEIGHT)
	{
		mlx_put_pixel(cub3d->main_img, x, y, cub3d->map->hex_flr);
		y++;
	}
}
