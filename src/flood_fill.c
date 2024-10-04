/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:52:02 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/04 14:47:44 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Flood fill to ensure the player is surrounded by walls
void	ft_flood_fill(char **tab, int pos_y, int pos_x, int *is_surrounded)
{
	if (pos_x < 0 || pos_y < 0 || tab[pos_y] == NULL
		|| tab[pos_y][pos_x] == '\0' || tab[pos_y][pos_x] == '1')
		return ;
	if (tab[pos_y][pos_x] != '0' && tab[pos_y][pos_x] != 'N'
		&& tab[pos_y][pos_x] != 'S' && tab[pos_y][pos_x] != 'E'
		&& tab[pos_y][pos_x] != 'W')
		return ;
	tab[pos_y][pos_x] = 'V';
	if (pos_x == 0 || pos_y == 0 || tab[pos_y + 1] == NULL || tab[pos_y][pos_x \
		+ 1] == '\0' || tab[pos_y][pos_x + 1] == ' ')
		*is_surrounded = 0;
	ft_flood_fill(tab, pos_y, pos_x - 1, is_surrounded);
	ft_flood_fill(tab, pos_y, pos_x + 1, is_surrounded);
	ft_flood_fill(tab, pos_y - 1, pos_x, is_surrounded);
	ft_flood_fill(tab, pos_y + 1, pos_x, is_surrounded);
}
