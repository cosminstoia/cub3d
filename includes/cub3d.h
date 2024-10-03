/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:44:25 by gstronge          #+#    #+#             */
/*   Updated: 2024/10/03 17:37:46 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.141592654
# define WNDW_WIDTH 1600
# define WNDW_HEIGHT 1200
# define MAP_SIZE 700

typedef struct s_map
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	unsigned long	hex_flr;
	unsigned long	hex_clg;
	char			**m_arr;
	char			**mapcopy;
	int				width;
	int				height;
	int				scale;
	int				width_pix;
	int				height_pix;
	int				cf_flag;
	int				texture_flag;
}					t_map;

typedef struct s_player
{
	int				p_flag;
	double			pos_x;
	double			pos_y;
	double			dx;
	double			dy;
	double			angle;
}					t_player;

typedef struct s_cub3d
{
	mlx_t			*mlx;
	t_map			*map;
	t_player		*player;
	mlx_image_t		*map_img;
	mlx_image_t		*main_img;
	mlx_texture_t	*texture_array[4];
}					t_cub3d;

typedef struct s_line
{
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				dx;
	int				dy;
	float			slope_err;
}					t_line;

typedef struct s_ray
{
	double			dx;
	double			dy;
	double			end_x;
	double			end_y;
	double			step;
	double			len;
	bool			is_north_or_south;
	mlx_texture_t	*texture;
}					t_ray;

// draw_minimap.c
void				ft_draw_map(t_cub3d *cub3d, t_map *map);
void				ft_print_block(t_cub3d *cub3d, int arr_x, int arr_y,
						u_int32_t colour);
void				ft_draw_player(t_cub3d *cub3d, t_player *player, int scale);

// raycasting.c
int					ft_draw_ray(t_cub3d *cub3d, t_player *player,
						float orig_angle, int x);
t_ray				ft_ray_vert_init(t_cub3d *cub3d, t_player *player);
t_ray				ft_ray_vert(t_cub3d *cub3d, t_player *player,
						t_ray vrt_ray);
t_ray				ft_ray_horiz_init(t_cub3d *cub3d, t_player *player);
t_ray				ft_ray_horiz(t_cub3d *cub3d, t_player *player,
						t_ray hrz_ray);

// move_player.c
void				ft_move_player(void *param);
int					ft_no_wall_crash(t_cub3d *cub3d, double x_adjust,
						double y_adjust);
void				ft_direction_keypress(t_cub3d *cub3d, double dx, double dy);
void				ft_rotation_keypress(t_cub3d *cub3d, char direction);

// lines.c
void				ft_draw_line(t_cub3d *cub3d, t_player *player, t_ray ray,
						int scale);
t_line				ft_init_line(int start_x, int start_y, int end_x,
						int end_y);
void				ft_x_greater(t_line line, t_cub3d *cub3d, int step_x,
						int step_y);
void				ft_y_greater(t_line line, t_cub3d *cub3d, int step_x,
						int step_y);

// read_map.c
int					ft_read_input(t_cub3d *cub3d, char *input, t_map *map);

// check_map.c
void				ft_check_input(t_cub3d *cub3d, char *filename);

// main_img.c
void				ft_draw_main_img(t_cub3d *cub3d, t_ray ray,
						float orig_angle, int x);
double				ft_correct_fisheye(t_cub3d *cub3d, t_ray ray,
						double orig_angle);
void				ft_draw_clg_and_flr(t_cub3d *cub3d, int x, int y);

// textures_colors.c
void				ft_parse_textures_and_colors(t_cub3d *cub3d, char *line);

// player.c
int					ft_check_player_position(t_cub3d *cub3d, char c, int x,
						int y);

// flood_fill.c
void				flood_fill(char **tab, int pos_y, int pos_x,
						int *is_surrounded);

// cleanup.c
void				ft_cleanup(t_cub3d *cub3d, char *error_message, int errno);
void				ft_free_map(t_map *map);
void				ft_free_2d_array(char **array, int height);
void				ft_free_split(char **split);

// rgb_to_hex.c
unsigned long		ft_rgb_to_hex(t_cub3d *cub3d, int *rgb);

#endif