/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:19:07 by gstronge          #+#    #+#             */
/*   Updated: 2024/10/03 16:41:48 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_cleanup(t_cub3d *cub3d, char *error_message, int errno)
{
	int	i;

	i = 0;
	if (error_message != NULL)
		printf("%s", error_message);
	if (cub3d == NULL)
		exit(errno);
	if (cub3d->map)
		ft_free_map(cub3d->map);
	if (cub3d->player)
		free(cub3d->player);
	while (i < 4)
	{
		if (cub3d->texture_array[i])
			mlx_delete_texture(cub3d->texture_array[i]);
		i++;
	}
	if (cub3d->mlx)
		mlx_terminate(cub3d->mlx);
	free(cub3d);
	exit(errno);
}

void	ft_free_map(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->m_arr)
		ft_free_2d_array(map->m_arr, map->height);
	if (map->mapcopy)
		ft_free_2d_array(map->mapcopy, map->height);
	free(map);
}

void	ft_free_2d_array(char **array, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
