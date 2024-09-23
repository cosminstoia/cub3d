/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:27:27 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/23 13:30:36 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_move_player(void* param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	// printf("angle = %f, pos_x = %f, pos_y = %f\n", cub3d->player->angle, cub3d->player->pos_x, cub3d->player->pos_y);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))//move player forwards
	{
		if (ft_no_wall_crash(cub3d, cub3d->player->dx, cub3d->player->dy))
		{	
			cub3d->player->pos_x += cub3d->player->dx;
			cub3d->player->pos_y += cub3d->player->dy;
		}
		ft_draw_player(cub3d ,cub3d->player, cub3d->map->scale);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))//move player left
	{
		if (ft_no_wall_crash(cub3d, cub3d->player->dy, -cub3d->player->dx))
		{	
			cub3d->player->pos_x += cub3d->player->dy;
			cub3d->player->pos_y -= cub3d->player->dx;
		}
		ft_draw_player(cub3d ,cub3d->player, cub3d->map->scale);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))//move player backwards
	{
		if (ft_no_wall_crash(cub3d, -cub3d->player->dy, -cub3d->player->dx))
		{	
			cub3d->player->pos_x -= cub3d->player->dx;
			cub3d->player->pos_y -= cub3d->player->dy;
		}
		ft_draw_player(cub3d ,cub3d->player, cub3d->map->scale);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))//move player right
	{
		if (ft_no_wall_crash(cub3d, -cub3d->player->dy, cub3d->player->dx))
		{	
			cub3d->player->pos_x -= cub3d->player->dy;
			cub3d->player->pos_y += cub3d->player->dx;
		}
		ft_draw_player(cub3d ,cub3d->player, cub3d->map->scale);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))//rotate left
	{
		cub3d->player->angle -= 0.05;
		if (cub3d->player->angle < 0)
			cub3d->player->angle += PI * 2;
		cub3d->player->dx = cos(cub3d->player->angle) * 0.05;
		cub3d->player->dy = sin(cub3d->player->angle) * 0.05;
		ft_draw_player(cub3d ,cub3d->player, cub3d->map->scale);
	}
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))//rotate right
	{
		cub3d->player->angle += 0.05;
		if (cub3d->player->angle > (PI * 2))
			cub3d->player->angle -= PI * 2;
		cub3d->player->dx = cos(cub3d->player->angle) * 0.05;
		cub3d->player->dy = sin(cub3d->player->angle) * 0.05;
		ft_draw_player(cub3d ,cub3d->player, cub3d->map->scale);
	}
}

int	ft_no_wall_crash(t_cub3d *cub3d, float x_adjustment, float y_adjustment)
{
	float	new_pos_x;
	float	new_pos_y;

	new_pos_x = cub3d->player->pos_x + x_adjustment;
	new_pos_y = cub3d->player->pos_y + y_adjustment;
	if (cub3d->map->m_arr[(int)new_pos_y][(int)new_pos_x] == '1')
		return (0);
	return (1);
}
