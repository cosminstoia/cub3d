/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:36:48 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/23 17:48:34 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_draw_ray(t_cub3d *cub3d, t_player *player, float orig_angle, int x)
{
	t_ray vert_ray;
	t_ray horiz_ray;

	vert_ray = ft_ray_vert_init(player);
	vert_ray = ft_ray_vert(cub3d, player, vert_ray);
	horiz_ray = ft_ray_horiz_init(player);
	horiz_ray = ft_ray_horiz(cub3d, player, horiz_ray);

	if (vert_ray.len < horiz_ray.len)
	{
		ft_draw_line(cub3d, player->pos_x * cub3d->map->scale, player->pos_y * cub3d->map->scale, vert_ray.end_x * cub3d->map->scale, vert_ray.end_y * cub3d->map->scale);
		ft_draw_main_img(cub3d, vert_ray, orig_angle, x);
	}
	else
	{
		ft_draw_line(cub3d, player->pos_x * cub3d->map->scale, player->pos_y * cub3d->map->scale, horiz_ray.end_x * cub3d->map->scale, horiz_ray.end_y * cub3d->map->scale);
		ft_draw_main_img(cub3d, horiz_ray, orig_angle, x);	
	}
	return (0);
}

t_ray	ft_ray_vert_init(t_player *player)
{
	t_ray vert_ray;

	if (player->angle < 1.5 * PI && player->angle > 0.5 * PI)
	{
		vert_ray.end_x = floor(player->pos_x) - 0.001;
		vert_ray.dx = vert_ray.end_x - player->pos_x;
		vert_ray.step = -1;
	}
	else
	{
		vert_ray.end_x = ceil(player->pos_x) + 0.001;
		vert_ray.dx = vert_ray.end_x - player->pos_x;
		vert_ray.step = 1;
	}
	vert_ray.dy = tan(player->angle) * vert_ray.dx;
	vert_ray.end_y = player->pos_y + vert_ray.dy;
	return (vert_ray);
}

t_ray	ft_ray_vert(t_cub3d *cub3d, t_player *player, t_ray vert_ray)
{
	while (vert_ray.end_x >= 0 && vert_ray.end_x <= cub3d->map->width && vert_ray.end_y >= 0 && vert_ray.end_y <= cub3d->map->height && cub3d->map->m_arr[(int)(vert_ray.end_y)][(int)vert_ray.end_x] != '1')
	{
		vert_ray.dx += vert_ray.step;
		vert_ray.end_x += vert_ray.step;
		vert_ray.dy = tan(player->angle) * vert_ray.dx;
		vert_ray.end_y = player->pos_y + vert_ray.dy;
	}
	if (vert_ray.step == -1)
	{
		vert_ray.dx += 0.002;
		vert_ray.end_x += 0.002;
	}
	else
	{
		vert_ray.dx -= 0.002;
		vert_ray.end_x -= 0.002;
	}
	vert_ray.dy = tan(player->angle) * vert_ray.dx;
	vert_ray.end_y = player->pos_y + vert_ray.dy;
	vert_ray.len = sqrt((vert_ray.dx * vert_ray.dx) + (vert_ray.dy * vert_ray.dy));
	return (vert_ray);
}

t_ray	ft_ray_horiz_init(t_player *player)
{
	t_ray horiz_ray;

	if (player->angle >= PI)
	{
		horiz_ray.end_y = floor(player->pos_y) - 0.001;
		horiz_ray.dy = horiz_ray.end_y - player->pos_y;
		horiz_ray.step = -1;
	}
	else
	{
		horiz_ray.end_y = ceil(player->pos_y) + 0.001;
		horiz_ray.dy = horiz_ray.end_y - player->pos_y;
		horiz_ray.step = 1;
	}
	horiz_ray.dx = horiz_ray.dy / tan(player->angle);
	horiz_ray.end_x = player->pos_x + horiz_ray.dx;
	return (horiz_ray);
}

t_ray	ft_ray_horiz(t_cub3d *cub3d, t_player *player, t_ray horiz_ray)
{
	while (horiz_ray.end_x >= 0 && horiz_ray.end_x <= cub3d->map->width && horiz_ray.end_y >= 0 && horiz_ray.end_y <= cub3d->map->height && cub3d->map->m_arr[(int)(horiz_ray.end_y)][(int)horiz_ray.end_x] != '1')
	{
		horiz_ray.dy += horiz_ray.step;
		horiz_ray.end_y += horiz_ray.step;
		horiz_ray.dx = horiz_ray.dy / tan(player->angle);
		horiz_ray.end_x = player->pos_x + horiz_ray.dx;
	}
	if (horiz_ray.step == -1)
	{
		horiz_ray.dy += 0.002;
		horiz_ray.end_y += 0.002;
	}
	else
	{
		horiz_ray.dy -= 0.002;
		horiz_ray.end_y -= 0.002;
	}
	horiz_ray.dx = horiz_ray.dy / tan(player->angle);
	horiz_ray.end_y = player->pos_y + horiz_ray.dy;
	horiz_ray.len = sqrt((horiz_ray.dx * horiz_ray.dx) + (horiz_ray.dy * horiz_ray.dy));
	return (horiz_ray);
}
