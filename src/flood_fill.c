/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:52:02 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/02 11:56:57 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Flood fill to ensure the player is surrounded by walls
// void flood_fill(char **tab, int pos_y, int pos_x)
// {
//     if (pos_x < 0 || pos_y < 0 || tab[pos_y] == NULL
//	|| tab[pos_y][pos_x] == '\0' || tab[pos_y][pos_x] == '1')
//         return ;
//     if (tab[pos_y][pos_x] != '0' && tab[pos_y][pos_x] != '1')
//         return ;
//     tab[pos_y][pos_x] = 'V';
//     flood_fill(tab, pos_x - 1, pos_y);
//     flood_fill(tab, pos_x + 1, pos_y);
//     flood_fill(tab, pos_x, pos_y - 1);
//     flood_fill(tab, pos_x, pos_y + 1);
// }