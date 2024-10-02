/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:36:48 by gstronge          #+#    #+#             */
/*   Updated: 2024/10/01 17:08:50 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_draw_ray(t_cub3d *cub3d, t_player *player, float orig_angle, int x)
{
	t_ray	vrt_ray;
	t_ray	hrz_ray;

	vrt_ray = ft_ray_vert_init(cub3d, player);
	vrt_ray = ft_ray_vert(cub3d, player, vrt_ray);
	hrz_ray = ft_ray_horiz_init(cub3d, player);
	hrz_ray = ft_ray_horiz(cub3d, player, hrz_ray);
	if (vrt_ray.len < hrz_ray.len)
	{
		if (x % 50 == 0)
			ft_draw_line(cub3d, player, vrt_ray, cub3d->map->scale);
		ft_draw_main_img(cub3d, vrt_ray, orig_angle, x);
	}
	else
	{
		if (x % 50 == 0)
			ft_draw_line(cub3d, player, hrz_ray, cub3d->map->scale);
		ft_draw_main_img(cub3d, hrz_ray, orig_angle, x);
	}
	return (0);
}

t_ray	ft_ray_vert_init(t_cub3d *cub3d, t_player *player)
{
	t_ray	vrt_ray;

	vrt_ray.is_north_or_south = false;
	if (player->angle < 1.5 * PI && player->angle > 0.5 * PI)
	{
		vrt_ray.texture = cub3d->texture_array[2];
		vrt_ray.end_x = floor(player->pos_x) - 0.000001;
		vrt_ray.dx = vrt_ray.end_x - player->pos_x;
		vrt_ray.step = -1;
	}
	else
	{
		vrt_ray.texture = cub3d->texture_array[3];
		vrt_ray.end_x = ceil(player->pos_x) + 0.000001;
		vrt_ray.dx = vrt_ray.end_x - player->pos_x;
		vrt_ray.step = 1;
	}
	vrt_ray.dy = tan(player->angle) * vrt_ray.dx;
	vrt_ray.end_y = player->pos_y + vrt_ray.dy;
	return (vrt_ray);
}

t_ray	ft_ray_vert(t_cub3d *cub3d, t_player *player, t_ray vrt_ray)
{
	while (vrt_ray.end_x >= 0 && vrt_ray.end_x <= cub3d->map->width \
		&& vrt_ray.end_y >= 0 && vrt_ray.end_y <= cub3d->map->height \
		&& cub3d->map->m_arr[(int)(vrt_ray.end_y)][(int)vrt_ray.end_x] != '1')
	{
		vrt_ray.dx += vrt_ray.step;
		vrt_ray.end_x += vrt_ray.step;
		vrt_ray.dy = tan(player->angle) * vrt_ray.dx;
		vrt_ray.end_y = player->pos_y + vrt_ray.dy;
	}
	if (vrt_ray.step == -1)
	{
		vrt_ray.dx += 0.000002;
		vrt_ray.end_x += 0.000002;
	}
	else
	{
		vrt_ray.dx -= 0.000002;
		vrt_ray.end_x -= 0.000002;
	}
	vrt_ray.dy = tan(player->angle) * vrt_ray.dx;
	vrt_ray.end_y = player->pos_y + vrt_ray.dy;
	vrt_ray.len = sqrt((vrt_ray.dx * vrt_ray.dx) + (vrt_ray.dy * vrt_ray.dy));
	return (vrt_ray);
}

t_ray	ft_ray_horiz_init(t_cub3d *cub3d, t_player *player)
{
	t_ray	hrz_ray;

	hrz_ray.is_north_or_south = true;
	if (player->angle >= PI)
	{
		hrz_ray.texture = cub3d->texture_array[0];
		hrz_ray.end_y = floor(player->pos_y) - 0.000001;
		hrz_ray.dy = hrz_ray.end_y - player->pos_y;
		hrz_ray.step = -1;
	}
	else
	{
		hrz_ray.texture = cub3d->texture_array[1];
		hrz_ray.end_y = ceil(player->pos_y) + 0.000001;
		hrz_ray.dy = hrz_ray.end_y - player->pos_y;
		hrz_ray.step = 1;
	}
	hrz_ray.dx = hrz_ray.dy / tan(player->angle);
	hrz_ray.end_x = player->pos_x + hrz_ray.dx;
	return (hrz_ray);
}

t_ray	ft_ray_horiz(t_cub3d *cub3d, t_player *player, t_ray hrz_ray)
{
	while (hrz_ray.end_x >= 0 && hrz_ray.end_x <= cub3d->map->width \
		&& hrz_ray.end_y >= 0 && hrz_ray.end_y <= cub3d->map->height \
		&& cub3d->map->m_arr[(int)(hrz_ray.end_y)][(int)hrz_ray.end_x] != '1')
	{
		hrz_ray.dy += hrz_ray.step;
		hrz_ray.end_y += hrz_ray.step;
		hrz_ray.dx = hrz_ray.dy / tan(player->angle);
		hrz_ray.end_x = player->pos_x + hrz_ray.dx;
	}
	if (hrz_ray.step == -1)
	{
		hrz_ray.dy += 0.000002;
		hrz_ray.end_y += 0.000002;
	}
	else
	{
		hrz_ray.dy -= 0.000002;
		hrz_ray.end_y -= 0.000002;
	}
	hrz_ray.dx = hrz_ray.dy / tan(player->angle);
	hrz_ray.end_y = player->pos_y + hrz_ray.dy;
	hrz_ray.len = sqrt((hrz_ray.dx * hrz_ray.dx) + (hrz_ray.dy * hrz_ray.dy));
	return (hrz_ray);
}
