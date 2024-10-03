/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:27:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/10/03 16:21:34 by cstoia           ###   ########.fr       */
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

static void	ft_check_filename(t_cub3d *cub3d, const char *filename)
{
	const char	*extension = ft_strrchr(filename, '.');

	if (extension && ft_strncmp(extension, ".cub", 4) != 0)
		ft_cleanup(cub3d, "Error\nFile extension must be .cub\n", EXIT_FAILURE);
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
			ft_check_player_position(cub3d, c, x, y);
			y++;
		}
		x++;
	}
	if (cub3d->player->p_flag == 0)
		ft_cleanup(cub3d, "Error\nNumber of players invalid\n", EXIT_FAILURE);
}

static void	ft_check_texture_path(t_cub3d *cub3d, char *path)
{
	int			fd;
	const char	*extension;

	if (path == NULL)
		ft_cleanup(cub3d, "Error\nInvalid texture path\n", EXIT_FAILURE);
	extension = ft_strrchr(path, '.');
	if (extension == NULL || ft_strncmp(extension, ".png", 4) != 0)
		ft_cleanup(cub3d, "Error\nTexture extension must be .png\n",
			EXIT_FAILURE);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_cleanup(cub3d, "Error\nInvalid path\n", EXIT_FAILURE);
	close(fd);
}

void	ft_check_input(t_cub3d *cub3d, char *filename)
{
	int	is_surrounded;

	is_surrounded = 1;
	ft_check_filename(cub3d, filename);
	ft_check_charachetrs(cub3d);
	ft_check_texture_path(cub3d, cub3d->map->no);
	ft_check_texture_path(cub3d, cub3d->map->so);
	ft_check_texture_path(cub3d, cub3d->map->we);
	ft_check_texture_path(cub3d, cub3d->map->ea);
	flood_fill(cub3d->map->mapcopy, (int)cub3d->player->pos_y,
		(int)cub3d->player->pos_x, &is_surrounded);
	ft_free_2d_array(cub3d->map->mapcopy, cub3d->map->height);
	cub3d->map->mapcopy = NULL;
	if (!is_surrounded)
		ft_cleanup(cub3d, "Error\nThe player is not surrounded by walls\n",
			EXIT_FAILURE);
	if (cub3d->map->cf_flag != 2 || cub3d->map->texture_flag != 4)
		ft_cleanup(cub3d, "Error\nToo many or too less textures or colors\n",
			EXIT_FAILURE);
	cub3d->map->width_pix = cub3d->map->scale * cub3d->map->width;
	cub3d->map->height_pix = cub3d->map->scale * cub3d->map->height;
}
