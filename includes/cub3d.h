/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:44:25 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/17 11:00:23 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../MLX42/include/MLX42/MLX42.h"

# include <string.h>//remove this  -----------------------------------------------------------------------------

typedef struct s_cub3d
{
	mlx_t			*mlx;
	mlx_image_t		*player;
	mlx_image_t		*mini_map;
} t_cub3d;

typedef struct s_map
{
	int				**map_arr;
	int				width;
	int				height;
	int				scale;
	int				player_x;
	int				player_y;
} t_map;

#endif