/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:44:25 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/18 11:30:22 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define PI 3.141592654

# include <string.h>//remove this (needed for memcpy) -----------------------------------------------------------------------------

typedef struct s_map
{

	int				**m_arr;
	int				width;
	int				height;
	int				scale;
} t_map;

typedef struct s_player
{
	mlx_image_t		*p_img;
	double			pos_x;
	double			pos_y;
	double			dx;
	double			dy;
	double			p_angle;
} t_player;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	t_map			*map;
	t_player		*player;
	mlx_image_t		*map_img;
} t_cub3d;

// draw_minimap.c
void	ft_draw_map(t_cub3d *cub3d, t_map *map);
void	ft_print_block(t_cub3d *cub3d, int arr_x, int arr_y, u_int32_t colour);
void	ft_draw_player(t_cub3d *cub3d, t_player *player, int scale);

// move_player.c
void	ft_move_player(void* param);
int		ft_no_wall_crash(t_cub3d *cub3d, float x_adjust, float y_adjust);

#endif