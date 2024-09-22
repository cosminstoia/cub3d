/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:27:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/22 15:13:12 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_walls(t_map *map)
{
	int	x;
	int	y;

	x = 1;
	y = 0;
	while (x < map->width)
	{
		if (map->m_arr[0][x - 1] != '1' && map->m_arr[0][x - 1] != ' ')
		{
			ft_printf("Error:\nInvalid walls!");
			exit(EXIT_FAILURE);
		}
		x++;
	}
	while (y < map->height - 1)
	{
		if ((map->m_arr[y][0] != '1' || map->m_arr[y][map->width - 1] != '1'))
		{
			ft_printf("Error:\nInvalid walls!");
			exit(EXIT_FAILURE);
		}
		y++;
	}
	x = 1;
	while (x < map->width)
	{
		if (map->m_arr[map->height - 1][x - 1] != '1')
		{
			ft_printf("Error:\nInvalid walls!");
			exit(EXIT_FAILURE);
		}
		x++;
	}
}

static int	check_character_position(t_player *player, char c, int i, int j)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != '\0')
	{
		ft_printf("Error:\nInvalid characters");
		exit(EXIT_FAILURE);
	}
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		player->pos_x = i;
		player->pos_y = j;
		player->p_flag++;
	}
	if (c == 'N')
		player->angle = PI * 1.5;
	if (c == 'E')
		player->angle = 0;
	if (c == 'S')
		player->angle = PI * 0.5;
	if (c == 'W')
		player->angle = PI;
	return (EXIT_SUCCESS);
}

static int	check_character(t_cub3d *cub3d)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < cub3d->map->height)
	{
		j = 0;
		while (j < cub3d->map->width)
		{
			c = cub3d->map->m_arr[i][j];
			check_character_position(cub3d->player, c, j, i);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	validate_map(t_cub3d *cub3d)
{
	cub3d->player->p_flag = 0;
	check_walls(cub3d->map);
	check_character(cub3d);
	cub3d->map->scale = 100;//need a function to calculate this --------------------------------
	cub3d->map->width_pix = cub3d->map->scale * cub3d->map->width;
	cub3d->map->height_pix = cub3d->map->scale * cub3d->map->height;
	cub3d->player->dx = 0;//need a function to calculate the dx and dy based on the direction of the player
	cub3d->player->dy = -0.05;//need a function to calculate the dx and dy based on the direction of the player
	return (EXIT_SUCCESS);
}