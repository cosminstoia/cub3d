/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:17:32 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/28 15:57:02 by cstoia           ###   ########.fr       */
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
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

static void	parse_textures_and_colors(t_map *map, char *line)
{
	char	**split_line;
	char	**rgb_values;

	split_line = ft_split(line, ' ');
	if (!split_line[1])
	{
		printf("Error:\nNo space between texture/color identifiers and path/codes.\n");
		//ft_cleanup();
		exit(EXIT_FAILURE);
	}
	if (split_line[0] && !ft_strncmp(split_line[0], "NO", 2))
		map->no = ft_strdup(ft_strtrim(split_line[1], " \n"));
	else if (split_line[0] && !ft_strncmp(split_line[0], "SO", 2))
		map->so = ft_strdup(ft_strtrim(split_line[1], " \n"));
	else if (split_line[0] && !ft_strncmp(split_line[0], "WE", 2))
		map->we = ft_strdup(ft_strtrim(split_line[1], " \n"));
	else if (split_line[0] && !ft_strncmp(split_line[0], "EA", 2))
		map->ea = ft_strdup(ft_strtrim(split_line[1], " \n"));
	else if (split_line[0] && !ft_strncmp(split_line[0], "F", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		map->floor[0] = ft_atoi(ft_strtrim(rgb_values[0], " \n"));
		map->floor[1] = ft_atoi(ft_strtrim(rgb_values[1], " \n"));
		map->floor[2] = ft_atoi(ft_strtrim(rgb_values[2], " \n"));
		map->hex_flr = rgb_to_hex(map->floor);
		// ft_cleanup(cub3d);
	}
	else if (split_line[0] && !ft_strncmp(split_line[0], "C", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		map->ceiling[0] = ft_atoi(ft_strtrim(rgb_values[0], " \n"));
		map->ceiling[1] = ft_atoi(ft_strtrim(rgb_values[1], " \n"));
		map->ceiling[2] = ft_atoi(ft_strtrim(rgb_values[2], " \n"));
		map->hex_clg = rgb_to_hex(map->ceiling);
		// ft_cleanup(cub3d);
	}
	// ft_cleanup(cub3d);
}

static void	fill_empty_space(t_map *map)
{
	int		i;
	int		j;
	char	*new_line;
	int		line_length;

	i = 0;
	while (map->m_arr[i])
	{
		line_length = ft_strlen(map->m_arr[i]);
		if (line_length < map->width)
		{
			new_line = ft_calloc(map->width + 1, sizeof(char));
			j = 0;
			while (map->m_arr[i][j])
			{
				new_line[j] = map->m_arr[i][j];
				j++;
			}
			while (j < map->width)
			{
				new_line[j] = ' ';
				j++;
			}
			new_line[j] = '\0';
			free(map->m_arr[i]);
			map->m_arr[i] = new_line;
		}
		i++;
	}
}

int	read_input(char *input, t_map *map)
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
	map->mapcopy = ft_split(concatenated_lines, '\n');
	fill_empty_space(map);
	if (map->width > map->height)
		map->scale = MAP_SIZE / map->width;
	else
		map->scale = MAP_SIZE / map->height;
	free(concatenated_lines);
	close(fd);
	return (EXIT_SUCCESS);
}