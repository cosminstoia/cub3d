/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:27:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/25 11:38:11 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Check top wall check bottom wall
static void	check_top_and_bot_wall(t_map *map)
{
	size_t	x;
	size_t	row_length;

	x = 0;
	while (x < ft_strlen(map->m_arr[0]))
	{
		if (map->m_arr[0][x] != '1' && map->m_arr[0][x] != ' ')
		{
			printf("Error:\nInvalid wall at top boundary");
			exit(EXIT_FAILURE);
		}
		x++;
	}
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

// Check left wall check right wall only if within bounds
static void	check_left_and_right_wall(t_map *map)
{
	int		y;
	size_t	row_length;

	row_length = ft_strlen(map->m_arr[0]);
	y = 0;
	while (y < map->height)
	{
		if (map->m_arr[y][0] != '1' && map->m_arr[y][0] != ' ')
		{
			printf("Error:\nInvalid wall at left boundary");
			exit(EXIT_FAILURE);
		}
		row_length = ft_strlen(map->m_arr[y]);
		if (row_length == 0 || (map->m_arr[y][row_length - 1] != '1'
				&& map->m_arr[y][row_length - 1] != ' '))
		{
			printf("Error:\nInvalid wall at right boundary");
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

// Store the data for the player
static void	store_player_data(t_player *player, double angle, double dx,
		double dy)
{
	player->angle = PI * angle;
	player->dx = dx;
	player->dy = dy;
}

// Check for invalid charachters and find the position of the player
static int	check_character_position(t_player *player, char c, int i, int j)
{
	if ((c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
			&& c != ' ') || player->p_flag >= 2)
	{
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
		store_player_data(player, 1.5, 0, -0.05);
	if (c == 'E')
		store_player_data(player, 0, +0.05, 0);
	if (c == 'S')
		store_player_data(player, 0.5, 0, +0.05);
	if (c == 'W')
		store_player_data(player, 1, -0.05, 0);
	return (EXIT_SUCCESS);
}

// Update the widht of each line from the map
int	find_line_width(const char *map)
{
	int			max_width;
	const char	*line;
	const char	*next_line;
	int			current_width;

	max_width = 0;
	line = map;
	next_line = ft_strchr(line, '\n');
	while (*line)
	{
		if (!next_line)
			next_line = line + ft_strlen(line);
		current_width = next_line - line;
		if (current_width > max_width)
			max_width = current_width;
		if (*next_line)
			line = next_line + 1;
		else
			line = next_line;
		next_line = ft_strchr(line, '\n');
	}
	return (max_width);
}

static void	check_filename(const char *filename)
{
	const char	*extension = ft_strrchr(filename, '.');

	if (extension && ft_strncmp(extension, ".cub", 4) != 0)
	{
		printf("Error\nFile extension must be .cub\n");
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
}

int	check_map(t_cub3d *cub3d, char *filename)
{
	int		i;
	int		j;
	char	c;
	int		width;

	i = 0;
	check_filename(filename);
	check_top_and_bot_wall(cub3d->map);
	check_left_and_right_wall(cub3d->map);
	while (i < cub3d->map->height)
	{
		width = find_line_width(cub3d->map->m_arr[i]);
		j = 0;
		while (j < width)
		{
			c = cub3d->map->m_arr[i][j];
			check_character_position(cub3d->player, c, j, i);
			j++;
		}
		i++;
	}
	if (cub3d->player->p_flag == 0)
	{
		printf("Error:\nNumber of player invalid!\n");
		exit(EXIT_FAILURE);
	}
	cub3d->map->width_pix = cub3d->map->scale * cub3d->map->width;
	cub3d->map->height_pix = cub3d->map->scale * cub3d->map->height;
	return (EXIT_SUCCESS);
}
