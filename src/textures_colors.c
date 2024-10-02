/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:22:16 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/02 15:05:40 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static unsigned long	ft_rgb_to_hex(int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error:\nRGB values must be between 0 and 255.\n");
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

// Function to parse texture paths (NO, SO, WE, EA)
static void	ft_parse_texture(t_map *map, char **split_line)
{
	if (!ft_strncmp(split_line[0], "NO", 2))
		map->no = ft_strdup(ft_strtrim(split_line[1], " \n"));
	else if (!ft_strncmp(split_line[0], "SO", 2))
		map->so = ft_strdup(ft_strtrim(split_line[1], " \n"));
	else if (!ft_strncmp(split_line[0], "WE", 2))
		map->we = ft_strdup(ft_strtrim(split_line[1], " \n"));
	else if (!ft_strncmp(split_line[0], "EA", 2))
		map->ea = ft_strdup(ft_strtrim(split_line[1], " \n"));
	else
	{
		printf("Error:\nUnknown texture identifier.\n");
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
	map->flag++;
}

// Function to parse RGB values for the floor
static void	ft_parse_floor_color(t_map *map, char **rgb_values)
{
	int	floor[3];

	if (!rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
	{
		printf("Error:\nInvalid RGB format. Expected 3 values.\n");
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
	floor[0] = ft_atoi(ft_strtrim(rgb_values[0], " \n"));
	floor[1] = ft_atoi(ft_strtrim(rgb_values[1], " \n"));
	floor[2] = ft_atoi(ft_strtrim(rgb_values[2], " \n"));
	map->hex_flr = ft_rgb_to_hex(floor);
	map->flag++;
}

// Function to parse RGB values for the ceiling
static void	ft_parse_ceiling_color(t_map *map, char **rgb_values)
{
	int	ceiling[3];

	if (!rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
	{
		printf("Error:\nInvalid RGB format. Expected 3 values.\n");
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
	ceiling[0] = ft_atoi(ft_strtrim(rgb_values[0], " \n"));
	ceiling[1] = ft_atoi(ft_strtrim(rgb_values[1], " \n"));
	ceiling[2] = ft_atoi(ft_strtrim(rgb_values[2], " \n"));
	map->hex_clg = ft_rgb_to_hex(ceiling);
	map->flag++;
}

// Main function to parse textures and colors
void	ft_parse_textures_and_colors(t_map *map, char *line)
{
	char	**split_line;
	char	**rgb_values;

	split_line = ft_split(line, ' ');
	if (!split_line[1])
	{
		printf("Error:\nNo space between identifiers and path/codes.\n");
		// ft_cleanup();
		exit(EXIT_FAILURE);
	}
	if (!ft_strncmp(split_line[0], "F", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		ft_parse_floor_color(map, rgb_values);
	}
	else if (!ft_strncmp(split_line[0], "C", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		ft_parse_ceiling_color(map, rgb_values);
	}
	else
		ft_parse_texture(map, split_line);
}
