/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:17:32 by cstoia            #+#    #+#             */
/*   Updated: 2024/09/22 15:15:18 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	map_size(t_map *map, char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	if (line[0] == '\n')
	{
		ft_printf("Error:\nInvalid map!");
		exit(EXIT_FAILURE);
	}
	if (len > map->width)
		map->width = len;
	map->height++;
}

int	read_map(char *input, t_map *map)
{
	int		fd;
	char	*line;
	char	*concatenated_lines;

	concatenated_lines = ft_calloc(1, 1);
	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error:\nInvalid file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		concatenated_lines = ft_strjoin_and_free(concatenated_lines, line);
		free(line);
		map_size(map, line);
		line = get_next_line(fd);
	}
	map->m_arr = ft_split(concatenated_lines, '\n');
	free(concatenated_lines);
	close(fd);
	return (EXIT_SUCCESS);
}

// int TEMP_copy_map_array(t_map *map)
// {
// 	int row0[] = {1,1,1,1,1,1,1};
// 	int row1[] = {1,0,1,0,0,0,1};
// 	int row2[] = {1,0,1,1,0,0,1};
// 	int row3[] = {1,0,0,0,0,0,1};
// 	int row4[] = {1,0,0,0,0,2,1};
// 	int row5[] = {1,1,1,1,1,1,1};

// 	memcpy(map->m_arr[0], row0, sizeof(row0));
// 	memcpy(map->m_arr[1], row1, sizeof(row1));
// 	memcpy(map->m_arr[2], row2, sizeof(row2));
// 	memcpy(map->m_arr[3], row3, sizeof(row3));
// 	memcpy(map->m_arr[4], row4, sizeof(row4));
// 	memcpy(map->m_arr[5], row5, sizeof(row5));
// 	return (0);
// }
// int i;

// i = 0;
// map->scale = 100;//TEMP: need to figure out a way to scale it correctly to fit in the top corner
// map->width = 7;//TEMP: need to calculate this from the parsing
// map->height = 6;//TEMP: need to calculate this from the parsing
// map->m_arr = malloc(map->height * sizeof(int *));
// if (!map->m_arr)
// 	return(-1);
// while (i < map->height)
// {
// 	map->m_arr[i] = malloc(map->width * sizeof(int));
// 	if (!map->m_arr[i])
// 		return(-1);
// 	i++;
// }

// TEMP_copy_map_array(map);//TEMP: temp function so ray casting can be done with test map before parsing is done correctly

// return (0);