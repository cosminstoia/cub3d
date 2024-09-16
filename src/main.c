/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:56:56 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/16 14:30:57 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_move_player(void* param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;

	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		cub3d->player->instances[0].y -= 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		cub3d->player->instances[0].y += 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		cub3d->player->instances[0].x -= 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		cub3d->player->instances[0].x += 5;
}

void ft_make_player(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			mlx_put_pixel(cub3d->player, x, y, 42424242);
			y++;
		}
		x++;		
	}
}

int main(void)
{
	t_cub3d		cub3d;

	cub3d.mlx = mlx_init(1000, 1000, "Cub3D", false);
	cub3d.player = mlx_new_image(cub3d.mlx, 5, 5);
	mlx_image_to_window(cub3d.mlx, cub3d.player, 500, 500);
	ft_make_player(&cub3d);

	mlx_loop_hook(cub3d.mlx, ft_move_player, &cub3d);
	mlx_loop(cub3d.mlx);
	mlx_terminate(cub3d.mlx);
	return (0);
}