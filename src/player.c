/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:55:12 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/03 14:26:56 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Store the data for the player
static void	ft_store_player_data(t_cub3d *cub3d, double angle, double dx,
		double dy)
{
	cub3d->player->angle = PI * angle;
	cub3d->player->dx = dx;
	cub3d->player->dy = dy;
}

// Check for invalid charachters and find the position of the player
int	ft_check_player_position(t_cub3d *cub3d, char c, int x, int y)
{
	if ((c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
			&& c != ' ') || cub3d->player->p_flag >= 2)
		ft_cleanup(cub3d, "Error\nInvalid characters\n", EXIT_FAILURE);
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		cub3d->player->pos_x = y;
		cub3d->player->pos_y = x;
		cub3d->player->p_flag++;
		if (c == 'N')
			ft_store_player_data(cub3d, 1.5, 0, -0.05);
		else if (c == 'E')
			ft_store_player_data(cub3d, 0, +0.05, 0);
		else if (c == 'S')
			ft_store_player_data(cub3d, 0.5, 0, +0.05);
		else if (c == 'W')
			ft_store_player_data(cub3d, 1, -0.05, 0);
	}
	return (EXIT_SUCCESS);
}
