/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_to_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:37:00 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/03 17:38:23 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned long	ft_rgb_to_hex(t_cub3d *cub3d, int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_cleanup(cub3d, "Error\nRGB values must be between 0 and 255\n",
			EXIT_FAILURE);
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}
