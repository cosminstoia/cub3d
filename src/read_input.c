/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:17:32 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/06 12:46:33 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Function to get the size of the map
static void	ft_map_size(t_cub3d *cub3d, t_map *map, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len == 0)
		ft_cleanup(cub3d, "Error\nInvalid map\n", EXIT_FAILURE);
	if (len > map->width)
		map->width = len;
	map->height++;
}

// Function to expand a single line to the map's width by filling with spaces
static void	ft_expand_line(t_cub3d *cub3d, char **line, int target_width)
{
	char	*new_line;
	int		j;

	new_line = ft_calloc(target_width + 1, sizeof(char));
	if (!new_line)
		ft_cleanup(cub3d, "Error\nMalloc failed\n", EXIT_FAILURE);
	j = 0;
	while ((*line)[j])
	{
		new_line[j] = (*line)[j];
		j++;
	}
	while (j < target_width)
	{
		new_line[j] = ' ';
		j++;
	}
	new_line[j] = '\0';
	free(*line);
	*line = new_line;
}

// Function to iterate through the map and expand lines where necessary
static void	ft_fill_map_spaces(t_cub3d *cub3d, char **map)
{
	int	i;
	int	line_length;

	i = 0;
	while (map[i])
	{
		line_length = ft_strlen(map[i]);
		if (line_length < cub3d->map->width)
			ft_expand_line(cub3d, &map[i], cub3d->map->width);
		i++;
	}
}

// Function to process each line and append map data or parse textures/colors
static void	ft_process_line(t_cub3d *cub3d, int fd, t_map *map,
		char **con_lines)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		ft_cleanup(cub3d, "Error:\nMalloc failed\n", EXIT_FAILURE);
	while (line && line[0] != '\0')
	{
		if (line[0] != '\n')
		{
			if (ft_strncmp(line, "0", 1) != 0 && ft_strncmp(line, "1", 1) != 0
				&& ft_strncmp(line, " ", 1) != 0)
				ft_parse_textures_and_colors(cub3d, line);
			else
			{
				*con_lines = ft_strjoin_and_free(*con_lines, line);
				ft_map_size(cub3d, map, line);
			}
		}
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			ft_cleanup(cub3d, "Error:\nMalloc failed\n", EXIT_FAILURE);
	}
	if (line[0] == '\0')
		free(line);
}

// Main function to read input file, process lines, and finalize the map
int	ft_read_input(t_cub3d *cub3d, char *input, t_map *map)
{
	int		fd;
	char	*concatenated_lines;

	concatenated_lines = ft_calloc(1, 1);
	fd = open(input, O_RDONLY);
	if (fd == -1)
		ft_cleanup(cub3d, "Error\nInvalid file\n", EXIT_FAILURE);
	ft_process_line(cub3d, fd, map, &concatenated_lines);
	map->m_arr = ft_split(concatenated_lines, '\n');
	if (!map->m_arr)
		ft_cleanup(cub3d, "Error\nMalloc failed\n", EXIT_FAILURE);
	map->mapcopy = ft_split(concatenated_lines, '\n');
	if (!map->mapcopy)
		ft_cleanup(cub3d, "Error\nMalloc failed\n", EXIT_FAILURE);
	ft_fill_map_spaces(cub3d, map->m_arr);
	ft_fill_map_spaces(cub3d, map->mapcopy);
	if (map->width == 0 && map->height == 0)
		ft_cleanup(cub3d, "Error\nNo map\n", EXIT_FAILURE);
	if (map->width > map->height)
		map->scale = MAP_SIZE / map->width;
	else
		map->scale = MAP_SIZE / map->height;
	free(concatenated_lines);
	close(fd);
	return (EXIT_SUCCESS);
}
