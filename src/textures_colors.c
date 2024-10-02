/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:22:16 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/02 18:13:55 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static unsigned long	ft_rgb_to_hex(t_cub3d *cub3d, int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_cleanup(cub3d, "Error\nRGB values must be between 0 and 255\n", EXIT_FAILURE);
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

// Function to parse texture paths (NO, SO, WE, EA)
static void	ft_parse_texture(t_cub3d *cub3d, t_map *map, char **split_line)
{
	char	*temp;

	temp = ft_strtrim(split_line[1], "\n");
	if (!ft_strncmp(split_line[0], "NO", 2))
		map->no = ft_strdup(temp);
	else if (!ft_strncmp(split_line[0], "SO", 2))
		map->so = ft_strdup(temp);
	else if (!ft_strncmp(split_line[0], "WE", 2))
		map->we = ft_strdup(temp);
	else if (!ft_strncmp(split_line[0], "EA", 2))
		map->ea = ft_strdup(temp);
	else
	{
		free(temp);
		ft_cleanup(cub3d, "Error\nUnknown texture identifier\n", EXIT_FAILURE);
	}
	free(temp);
	map->flag++;
}

// Function to parse RGB values for the floor
static void	ft_parse_floor_color(t_cub3d *cub3d, t_map *map, char **rgb_values)
{
	int		floor[3];
	char	*temp;
	int		i;

	i = 0;
	if (!rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
		ft_cleanup(cub3d, "Error\nInvalid RGB format. Expected 3 values.\n", EXIT_FAILURE);
	while (i < 3)
	{
		temp = ft_strtrim(rgb_values[i], "\n");
		if (temp == NULL)
			ft_cleanup(cub3d, "Error\nmalloc failed\n", EXIT_FAILURE);
		floor[i] = ft_atoi(temp);
		free(temp);
		free(rgb_values[i]);
		i++;
	}
	while (rgb_values[i])
	{
		free(rgb_values[i]);
		i++;
	}
	free(rgb_values);
	map->hex_flr = ft_rgb_to_hex(cub3d, floor);
	map->flag++;
}

// Function to parse RGB values for the ceiling
static void	ft_parse_ceiling_color(t_cub3d *cub3d, t_map *map, char **rgb_values)
{
	int		ceiling[3];
	char	*temp;
	int		i;

	i = 0;
	if (!rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
		ft_cleanup(cub3d, "Error\nInvalid RGB format. Expected 3 values.\n", EXIT_FAILURE);
	while (i < 3)
	{
		temp = ft_strtrim(rgb_values[i], "\n");
		if (temp == NULL)
			ft_cleanup(cub3d, "Error\nmalloc failed\n", EXIT_FAILURE);
		ceiling[i] = ft_atoi(temp);
		free(temp);
		free(rgb_values[i]);
		i++;
	}
	while (rgb_values[i])
	{
		free(rgb_values[i]);
		i++;
	}
	free(rgb_values);
	map->hex_clg = ft_rgb_to_hex(cub3d, ceiling);
	map->flag++;
}

// Main function to parse textures and colors
void	ft_parse_textures_and_colors(t_cub3d *cub3d, t_map *map, char *line)
{
	char	**split_line;
	char	**rgb_values;

	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		ft_cleanup(cub3d, "Error\nMalloc failed\n", EXIT_FAILURE);
	if (!split_line[1])
		ft_cleanup(cub3d, "Error\nNo space between identifiers and path/codes\n", EXIT_FAILURE);
	if (!ft_strncmp(split_line[0], "F", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		ft_parse_floor_color(cub3d, map, rgb_values);
	}
	else if (!ft_strncmp(split_line[0], "C", 1))
	{
		rgb_values = ft_split(split_line[1], ',');
		ft_parse_ceiling_color(cub3d, map, rgb_values);
	}
	else
		ft_parse_texture(cub3d, map, split_line);
	ft_free_split(split_line);
}
