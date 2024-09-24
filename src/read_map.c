/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:17:32 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/24 18:37:27 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	map_size(t_map *map, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len == 0)
	{
		printf("Error:\nInvalid map!");
		exit(EXIT_FAILURE);
	}
	if (len > map->width)
		map->width = len;
	map->height++;
}

static unsigned long	rgb_to_hex(int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	return (((r & 0xff) << 24) + ((g & 0xff) << 16) + (b & 0xff << 8) + (255 & 0xff));
}

static void	parse_textures_and_colors(t_map *map, char *line)
{
	char	**split_line;
	char	**rgb_values;

	split_line = ft_split(line, ' ');
	if (split_line[0] && !ft_strncmp(split_line[0], "NO", 2))
		map->no = ft_strdup(split_line[1]);
	else if (split_line[0] && !ft_strncmp(split_line[0], "SO", 2))
		map->so = ft_strdup(split_line[1]);
	else if (split_line[0] && !ft_strncmp(split_line[0], "WE", 2))
		map->we = ft_strdup(split_line[1]);
	else if (split_line[0] && !ft_strncmp(split_line[0], "EA", 2))
		map->ea = ft_strdup(split_line[1]);
	else if (split_line[0] && !ft_strncmp(split_line[0], "F", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		map->floor[0] = ft_atoi(rgb_values[0]);
		map->floor[1] = ft_atoi(rgb_values[1]);
		map->floor[2] = ft_atoi(rgb_values[2]);
		map->hex_flr = rgb_to_hex(map->floor);
		// ft_cleanup(cub3d);
	}
	else if (split_line[0] && !ft_strncmp(split_line[0], "C", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		map->ceiling[0] = ft_atoi(rgb_values[0]);
		map->ceiling[1] = ft_atoi(rgb_values[1]);
		map->ceiling[2] = ft_atoi(rgb_values[2]);
		map->hex_clg = rgb_to_hex(map->ceiling);
		// ft_cleanup(cub3d);
	}
	// ft_cleanup(cub3d);
}

int	read_map(char *input, t_map *map)
{
	int fd;
	char *line;
	char *concatenated_lines;

	concatenated_lines = ft_calloc(1, 1);
	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		printf("Error:\nInvalid file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_strncmp(line, "1", 1) != 0 && ft_strncmp(line, " ", 1) != 0)
			parse_textures_and_colors(map, line);
		else
		{
			concatenated_lines = ft_strjoin_and_free(concatenated_lines, line);
			map_size(map, line);
		}
		free(line);
		line = get_next_line(fd);
	}

	map->m_arr = ft_split(concatenated_lines, '\n');
	if (map->width > map->height)
		map->scale = MAP_SIZE / map->width;
	else
		map->scale = MAP_SIZE / map->height;
	free(concatenated_lines);
	close(fd);
	return (EXIT_SUCCESS);
}