/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:31:50 by gstronge          #+#    #+#             */
/*   Updated: 2024/09/19 16:21:13 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_line(t_cub3d *cub3d, int start_x, int start_y, int end_x, int end_y)
{
	t_line_pts	line;
	int			step_x;
	int			step_y;

	if (line.start_x < line.end_x)
		step_x = 1;
	else
		step_x = -1;
	if (line.start_y < line.end_y)
		step_y = 1;
	else
		step_y = -1;
	line = ft_init_line(start_x, start_y, end_x, end_y);

	if (line.dx >= abs(line.dy))
		ft_x_greater(line, cub3d, step_x, step_y);
	else
		ft_y_greater(line, cub3d, step_x, step_y);
}

t_line_pts	ft_init_line(int start_x, int start_y, int end_x, int end_y)
{
	t_line_pts line;

	line.start_x = end_x;
	line.end_x = start_x;
	line.start_y = end_y;
	line.end_y = start_y;
	line.dx = abs(end_x - start_x);
	line.dy = abs(end_y - start_y);
	return(line);
}

void	ft_x_greater(t_line_pts line, t_cub3d *cub3d, int step_x, int step_y)
{
	line.slope_err = line.dx / 2;
	while (line.start_x != line.end_x && line.start_x < 1000 && line.start_x > 0)
	{
		line.start_x += step_x;
		line.slope_err = line.slope_err - abs(line.dy);
		if (line.slope_err <= 0)
		{
			line.slope_err = line.slope_err + abs(line.dx);
			line.start_y += step_y;
		}
		if (line.start_x >= 0 && line.start_x <= (cub3d->map->width * cub3d->map->scale) && line.start_y >= 0 && line.start_y <= (cub3d->map->height * cub3d->map->scale))
			mlx_put_pixel(cub3d->map_img, round(line.start_x), round(line.start_y), 0xFF0000FF);
	}
}

void	ft_y_greater(t_line_pts line, t_cub3d *cub3d, int step_x, int step_y)
{
	line.slope_err = abs(line.dy) / 2;
	while (line.start_y != line.end_y  && line.start_y < 1000 && line.start_y > 0)
	{
		line.start_y += step_y;
		line.slope_err = line.slope_err - line.dx;
		if (line.slope_err <= 0)
		{
			line.slope_err = line.slope_err + abs(line.dy);
			line.start_x += step_x;
		}
		if (line.start_x >= 0 && line.start_x <= (cub3d->map->width * cub3d->map->scale) && line.start_y >= 0 && line.start_y <= (cub3d->map->height * cub3d->map->scale))
			mlx_put_pixel(cub3d->map_img, round(line.start_x), round(line.start_y), 0xFF0000FF);
	}
}
