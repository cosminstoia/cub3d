/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:27:27 by gstronge          #+#    #+#             */
/*   Updated: 2024/10/01 15:05:58 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_move_player(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		ft_direction_keypress(cub3d, cub3d->player->dx, cub3d->player->dy);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		ft_direction_keypress(cub3d, cub3d->player->dy, -cub3d->player->dx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		ft_direction_keypress(cub3d, -cub3d->player->dx, -cub3d->player->dy);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		ft_direction_keypress(cub3d, -cub3d->player->dy, cub3d->player->dx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		ft_rotation_keypress(cub3d, 'L');
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		ft_rotation_keypress(cub3d, 'R');
}

int	ft_no_wall_crash(t_cub3d *cub3d, double x_adjust, double y_adjust)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = cub3d->player->pos_x + x_adjust;
	new_pos_y = cub3d->player->pos_y + y_adjust;
	if (cub3d->map->m_arr[(int)new_pos_y][(int)new_pos_x] == '1')
		return (0);
	return (1);
}

void	ft_direction_keypress(t_cub3d *cub3d, double dx, double dy)
{
	if (ft_no_wall_crash(cub3d, dx, dy))
	{
		cub3d->player->pos_x += dx;
		cub3d->player->pos_y += dy;
	}
	ft_draw_player(cub3d, cub3d->player, cub3d->map->scale);
}

void	ft_rotation_keypress(t_cub3d *cub3d, char direction)
{
	if (direction == 'L')
	{
		cub3d->player->angle -= 0.02;
		if (cub3d->player->angle < 0)
			cub3d->player->angle += PI * 2;
	}
	else if (direction == 'R')
	{
		cub3d->player->angle += 0.02;
		if (cub3d->player->angle > (PI * 2))
			cub3d->player->angle -= PI * 2;
	}
	cub3d->player->dx = cos(cub3d->player->angle) * 0.03;
	cub3d->player->dy = sin(cub3d->player->angle) * 0.03;
	ft_draw_player(cub3d, cub3d->player, cub3d->map->scale);
}
