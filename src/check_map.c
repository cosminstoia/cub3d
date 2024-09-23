/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:27:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/23 16:22:23 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_walls(t_map *map)
{
	int		y;
	size_t	x;
	size_t	row_length;

	// Check top wall
	row_length = ft_strlen(map->m_arr[0]);
	x = 0;
	while (x < row_length)
	{
		if (map->m_arr[0][x] != '1' && map->m_arr[0][x] != ' ')
		{
			printf("Error:\nInvalid wall at top boundary");
			exit(EXIT_FAILURE);
		}
		x++;
	}
	y = 0;
	while (y < map->height)
	{
		// Check left wall
		if (map->m_arr[y][0] != '1' && map->m_arr[y][0] != ' ')
		{
			printf("Error:\nInvalid wall at left boundary");
			exit(EXIT_FAILURE);
		}
		// Check right wall only if within bounds
		row_length = ft_strlen(map->m_arr[y]);
		if (row_length == 0 || (map->m_arr[y][row_length - 1] != '1'
				&& map->m_arr[y][row_length - 1] != ' '))
		{
			printf("Error:\nInvalid wall at right boundary");
			exit(EXIT_FAILURE);
		}
		y++;
	}
	// Check bottom wall
	row_length = ft_strlen(map->m_arr[map->height - 1]);
	x = 0;
	while (x < row_length)
	{
		if (map->m_arr[map->height - 1][x] != '1' && map->m_arr[map->height
			- 1][x] != ' ')
		{
			printf("Error:\nInvalid wall at bottom boundary");
			exit(EXIT_FAILURE);
		}
		x++;
	}
}

static int	check_character_position(t_player *player, char c, int i, int j)
{
	// if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
	// 	&& c != '\0' && c != ' ')
	// {
	// 	printf("Error:\nInvalid characters");
	// 	exit(EXIT_FAILURE);
	// }
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		player->pos_x = i;
		player->pos_y = j;
		player->p_flag++;
	}
	if (c == 'N')
	{
		player->angle = PI * 1.5;
		player->dx = 0;
		player->dy = -0.05;
	}
	if (c == 'E')
	{
		player->angle = 0;
		player->dx = +0.05;
		player->dy = 0;
	}
	if (c == 'S')
	{
		player->angle = PI * 0.5;
		player->dx = 0;
		player->dy = +0.05;
	}
	if (c == 'W')
	{
		player->angle = PI;
		player->dx = -0.05;
		player->dy = 0;
	}
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

int	check_map(t_cub3d *cub3d)
{
	check_walls(cub3d->map);
	check_character(cub3d);
	cub3d->map->width_pix = cub3d->map->scale * cub3d->map->width;
	cub3d->map->height_pix = cub3d->map->scale * cub3d->map->height;
	return (EXIT_SUCCESS);
}