/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:27:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/02 11:58:46 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Update the widht of each line from the map
int	ft_find_line_width(const char *map)
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

static void	ft_check_filename(const char *filename)
{
	const char	*extension = ft_strrchr(filename, '.');

	if (extension && ft_strncmp(extension, ".cub", 4) != 0)
	{
		printf("Error\nFile extension must be .cub\n");
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
}

static void	ft_check_charachetrs(t_cub3d *cub3d)
{
	int		x;
	int		y;
	char	c;
	int		width;

	x = 0;
	while (x < cub3d->map->height)
	{
		width = ft_find_line_width(cub3d->map->m_arr[x]);
		y = 0;
		while (y < width)
		{
			c = cub3d->map->m_arr[x][y];
			ft_check_player_position(cub3d->player, c, x, y);
			y++;
		}
		x++;
	}
	if (cub3d->player->p_flag == 0)
	{
		printf("Error:\nNumber of players invalid!\n");
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
}

static void	ft_check_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error:\nInvalid path %s\n", path);
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	ft_check_input(t_cub3d *cub3d, char *filename)
{
	ft_check_filename(filename);
	ft_check_charachetrs(cub3d);
	ft_check_texture_path(cub3d->map->no);
	ft_check_texture_path(cub3d->map->so);
	ft_check_texture_path(cub3d->map->we);
	ft_check_texture_path(cub3d->map->ea);
	// flood_fill(cub3d->map->mapcopy, cub3d->player->pos_x,
	// cub3d->player->pos_y);
	// if (cub3d->map->mapcopy[(int)cub3d->player->pos_y][(int)cub3d->player->pos_x] != 'V')
	// {
	//     printf("Error: Flood fill failed! The player is not surrounded by walls.\n");
	//    // exit(EXIT_FAILURE);
	// }
	// else
	//     printf("Flood fill succeeded!\n");
	if (cub3d->map->flag != 6)
	{
		printf("Error:\nToo many or too less textures or colors\n");
		// ft_cleanup(cub3d);
		exit(EXIT_FAILURE);
	}
	cub3d->map->width_pix = cub3d->map->scale * cub3d->map->width;
	cub3d->map->height_pix = cub3d->map->scale * cub3d->map->height;
	return (EXIT_SUCCESS);
}
