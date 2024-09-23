/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:27:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/23 12:33:47 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static void	check_walls(t_map *map)
// {
// 	int	x;
// 	int	y;

// 	x = 1;
// 	y = 0;
// 	while (x < map->width)
// 	{
// 		if (map->m_arr[0][x - 1] != '1' && map->m_arr[0][x - 1] != ' ')
// 		{
// 			printf("Error:\nInvalid walls!");
// 			exit(EXIT_FAILURE);
// 		}
// 		x++;
// 	}
// 	while (y < map->height - 1)
// 	{
// 		if ((map->m_arr[y][0] != '1' || map->m_arr[y][map->width - 1] != '1'))
// 		{
// 			printf("Error:\nInvalid walls!");
// 			exit(EXIT_FAILURE);
// 		}
// 		y++;
// 	}
// 	x = 1;
// 	while (x < map->width)
// 	{
// 		if (map->m_arr[map->height - 1][x - 1] != '1')
// 		{
// 			printf("Error:\nInvalid walls!");
// 			exit(EXIT_FAILURE);
// 		}
// 		x++;
// 	}
// }

static int	check_character_position(t_player *player, char c, int i, int j)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != '\0')
	{
		printf("---------\n");
		printf("%c", c);
		printf("Error:\nInvalid characters");
		exit(EXIT_FAILURE);
	}
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
			printf("%c", c);
			while (c == ' ')
				j++;
			check_character_position(cub3d->player, c, j, i);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_map(t_cub3d *cub3d)
{
	cub3d->player->p_flag = 0;
	//check_walls(cub3d->map);
	check_character(cub3d);
	cub3d->map->scale = 50;
	cub3d->map->width_pix = cub3d->map->scale * cub3d->map->width;
	cub3d->map->height_pix = cub3d->map->scale * cub3d->map->height;
	return (EXIT_SUCCESS);
}