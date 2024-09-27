/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:27:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/27 14:51:16 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Flood fill to ensure the player is surrounded by walls
static int	flood_fill(char **tab, int pos_x, int pos_y)
{
	int	result;

	if (pos_x < 0 || pos_y < 0 || tab[pos_y] == NULL
		|| tab[pos_y][pos_x] == '1')
		return (1);
	tab[pos_y][pos_x] = '1';
	result = 0;
	result = flood_fill(tab, pos_x - 1, pos_y);
	result = flood_fill(tab, pos_x + 1, pos_y);
	result = flood_fill(tab, pos_x, pos_y - 1);
	result = flood_fill(tab, pos_x, pos_y + 1);
	return (result);
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
static int	check_character_position(t_player *player, char c, int x, int y)
{
	if ((c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
			&& c != ' ') || player->p_flag >= 2)
	{
		printf("Error:\nInvalid characters");
		exit(EXIT_FAILURE);
	}
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		player->pos_x = x;
		player->pos_y = y;
		player->p_flag++;
		if (c == 'N')
			store_player_data(player, 1.5, 0, -0.05);
		else if (c == 'E')
			store_player_data(player, 0, +0.05, 0);
		else if (c == 'S')
			store_player_data(player, 0.5, 0, +0.05);
		else if (c == 'W')
			store_player_data(player, 1, -0.05, 0);
	}
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

static void	check_charachetrs(t_cub3d *cub3d)
{
	int		x;
	int		y;
	char	c;
	int		width;

	x = 0;
	while (x < cub3d->map->height)
	{
		width = find_line_width(cub3d->map->m_arr[x]);
		y = 0;
		while (y < width)
		{
			c = cub3d->map->m_arr[x][y];
			check_character_position(cub3d->player, c, x, y);
			y++;
		}
		x++;
	}
	if (cub3d->player->p_flag == 0)
	{
		printf("Error:\nNumber of players invalid!\n");
		exit(EXIT_FAILURE);
	}
}

int	check_map(t_cub3d *cub3d, char *filename)
{
	check_filename(filename);
	check_charachetrs(cub3d);
	if (flood_fill(cub3d->map->mapcopy, cub3d->player->pos_x,
			cub3d->player->pos_y))
	{
		printf("Error: Flood fill failed! The player is not surrounded by walls.\n");
		// exit(EXIT_FAILURE);
	}
	cub3d->map->width_pix = cub3d->map->scale * cub3d->map->width;
	cub3d->map->height_pix = cub3d->map->scale * cub3d->map->height;
	return (EXIT_SUCCESS);
}
