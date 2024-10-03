/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:55:12 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/02 19:48:12 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Store the data for the player
static void	ft_store_player_data(t_player *player, double angle, double dx,
		double dy)
{
	player->angle = PI * angle;
	player->dx = dx;
	player->dy = dy;
}

// Check for invalid charachters and find the position of the player
int	ft_check_player_position(t_cub3d *cub3d, char c, int x, int y)
{
	if ((c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
			&& c != ' ') || cub3d->player->p_flag >= 2)
		ft_cleanup(cub3d, "Error:\nInvalid characters\n", EXIT_FAILURE);
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		cub3d->player->pos_x = y;
		cub3d->player->pos_y = x;
		cub3d->player->p_flag++;
		if (c == 'N')
			ft_store_player_data(cub3d->player, 1.5, 0, -0.05);
		else if (c == 'E')
			ft_store_player_data(cub3d->player, 0, +0.05, 0);
		else if (c == 'S')
			ft_store_player_data(cub3d->player, 0.5, 0, +0.05);
		else if (c == 'W')
			ft_store_player_data(cub3d->player, 1, -0.05, 0);
	}
	return (EXIT_SUCCESS);
}
