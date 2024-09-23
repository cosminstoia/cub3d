/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:17:32 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/23 15:52:58 by cstoia           ###   ########.fr       */
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

static void	parse_textures_and_colors(t_map *map, char *line)
{
	char	**split_line;
	char	**rgb_values;

	split_line = ft_split(line, ' ');
	if (split_line[0] && !ft_strncmp(split_line[0], "NO", 2))
		map->NO = ft_strdup(split_line[1]);
	else if (split_line[0] && !ft_strncmp(split_line[0], "SO", 2))
		map->SO = ft_strdup(split_line[1]);
	else if (split_line[0] && !ft_strncmp(split_line[0], "WE", 2))
		map->WE = ft_strdup(split_line[1]);
	else if (split_line[0] && !ft_strncmp(split_line[0], "EA", 2))
		map->EA = ft_strdup(split_line[1]);
	else if (split_line[0] && !ft_strncmp(split_line[0], "F", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		map->F[0] = ft_atoi(rgb_values[0]);
		map->F[1] = ft_atoi(rgb_values[1]);
		map->F[2] = ft_atoi(rgb_values[2]);
	}
	else if (split_line[0] && !ft_strncmp(split_line[0], "C", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		map->C[0] = ft_atoi(rgb_values[0]);
		map->C[1] = ft_atoi(rgb_values[1]);
		map->C[2] = ft_atoi(rgb_values[2]);
	}
	// free split_line and rgb_values here
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