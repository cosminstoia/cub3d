/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:22:16 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/04 14:08:05 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Function to parse texture paths (NO, SO, WE, EA)
static void	ft_assign_texture(t_cub3d *cub3d, char **split_line,
		char **texture_ptr)
{
	char	*temp;

	temp = ft_strtrim(split_line[1], "\n");
	free(*texture_ptr);
	*texture_ptr = temp;
	cub3d->map->texture_flag++;
}

static void	ft_parse_texture(t_cub3d *cub3d, char **split_line)
{
	if (!ft_strncmp(split_line[0], "NO", 2) && ft_strlen(split_line[0]) != 3)
		ft_assign_texture(cub3d, split_line, &cub3d->map->no);
	else if (!ft_strncmp(split_line[0], "SO", 2)
		&& ft_strlen(split_line[0]) != 3)
		ft_assign_texture(cub3d, split_line, &cub3d->map->so);
	else if (!ft_strncmp(split_line[0], "WE", 2)
		&& ft_strlen(split_line[0]) != 3)
		ft_assign_texture(cub3d, split_line, &cub3d->map->we);
	else if (!ft_strncmp(split_line[0], "EA", 2)
		&& ft_strlen(split_line[0]) != 3)
		ft_assign_texture(cub3d, split_line, &cub3d->map->ea);
	else
		ft_cleanup(cub3d, "Error\nUnknown identifier\n", EXIT_FAILURE);
}

// Function to parse RGB values from strings
static int	ft_parse_rgb_values(t_cub3d *cub3d, char **rgb_values,
		int colors[3])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (rgb_values[i][++j])
		{
			while (rgb_values[i][j] == ' ' || rgb_values[i][j] == '\n')
				j++;
			if (rgb_values[i][j] == '\0')
				break ;
			if (!ft_isdigit(rgb_values[i][j]))
				ft_cleanup(cub3d, "Error\nInvalid RGB codes.\n", EXIT_FAILURE);
		}
		colors[i] = ft_atoi(rgb_values[i]);
		if (colors[i] < 0 || colors[i] > 255)
			ft_cleanup(cub3d, "Error\nInvalid RGB values.\n", EXIT_FAILURE);
		free(rgb_values[i]);
	}
	return (i);
}

// Combined function to parse RGB values for either floor or ceiling
static void	ft_parse_color(t_cub3d *cub3d, char **rgb_values, char flag)
{
	int	colors[3];
	int	i;

	if ((flag == 'F' && cub3d->map->hex_flr) || \
			(flag == 'C' && cub3d->map->hex_clg))
		ft_cleanup(cub3d, "Error\nDuplicate colour\n", EXIT_FAILURE);
	if (!rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
		ft_cleanup(cub3d, "Error\nInvalid RGB format.\n", EXIT_FAILURE);
	i = ft_parse_rgb_values(cub3d, rgb_values, colors);
	while (rgb_values[i])
	{
		free(rgb_values[i]);
		i++;
	}
	free(rgb_values);
	if (flag == 'F')
		cub3d->map->hex_flr = ft_rgb_to_hex(cub3d, colors);
	else
		cub3d->map->hex_clg = ft_rgb_to_hex(cub3d, colors);
	cub3d->map->cf_flag++;
}

// Main function to parse textures and colors
void	ft_parse_textures_and_colors(t_cub3d *cub3d, char *line)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		ft_cleanup(cub3d, "Error\nMalloc failed\n", EXIT_FAILURE);
	if (!split_line[1] || ft_strlen(split_line[0]) > 2 || split_line[2] != NULL)
		ft_cleanup(cub3d, "Error\nInvalid identifiers.\n", EXIT_FAILURE);
	if (!ft_strncmp(split_line[0], "F", 2) && ft_strlen(split_line[0]) == 1)
		ft_parse_color(cub3d, ft_split(split_line[1], ','), 'F');
	else if (!ft_strncmp(split_line[0], "C", 2) && \
			ft_strlen(split_line[0]) == 1)
		ft_parse_color(cub3d, ft_split(split_line[1], ','), 'C');
	else
		ft_parse_texture(cub3d, split_line);
	ft_free_split(split_line);
}
