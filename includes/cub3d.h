/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:44:25 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/22 17:45:06 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define PI 3.141592654

typedef struct s_map
{

	char			**m_arr;
	int				width;
	int				height;
	int				scale;
	int				width_pix;
	int				height_pix;
} t_map;

typedef struct s_player
{
	int 			p_flag;
	mlx_image_t		*p_img;
	double			pos_x;
	double			pos_y;
	double			dx;
	double			dy;
	double			angle;
} t_player;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	t_map			*map;
	t_player		*player;
	mlx_image_t		*map_img;
} t_cub3d;

typedef struct s_line
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		dx;
	int		dy;
	float	slope_err;
} t_line;

typedef struct s_ray
{
	double	dx;
	double	dy;
	double	end_x;
	double	end_y;
	double	step;
	double	len;
} t_ray;

// draw_minimap.c
void		ft_draw_map(t_cub3d *cub3d, t_map *map);
void		ft_print_block(t_cub3d *cub3d, int arr_x, int arr_y, u_int32_t colour);
void		ft_draw_player(t_cub3d *cub3d, t_player *player, int scale);

// raycasting.c
int			ft_draw_ray(t_cub3d *cub3d, t_player *player, int scale);
t_ray		ft_ray_vert_init(t_player *player);
t_ray		ft_ray_vert(t_cub3d *cub3d, t_player *player, t_ray vert_ray);
t_ray		ft_ray_horiz_init(t_player *player);
t_ray		ft_ray_horiz(t_cub3d *cub3d, t_player *player, t_ray horiz_ray);

// move_player.c
void		ft_move_player(void* param);
int			ft_no_wall_crash(t_cub3d *cub3d, float x_adjust, float y_adjust);

// lines.c
void		ft_draw_line(t_cub3d *cub3d, int start_x, int start_y, int end_x, int end_y);
t_line		ft_init_line(int start_x, int start_y, int end_x, int end_y);
void		ft_x_greater(t_line line, t_cub3d *cub3d, int step_x, int step_y);
void		ft_y_greater(t_line line, t_cub3d *cub3d, int step_x, int step_y);

// read_map.c
int			read_map(char *input, t_map *map);

// check_map.c
int			validate_map(t_cub3d *cub3d);


#endif