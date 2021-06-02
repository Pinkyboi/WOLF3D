/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 20:41:53 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/29 20:41:55 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_calulate_errors(t_coor *error, t_coor *step,
	t_coor *sec_step, t_coor *start)
{
	error->y = 2 * error->x;
	if (error->y >= step->y)
	{
		error->x += step->y;
		start->x += sec_step->x;
	}
	if (error->y <= step->x)
	{
		error->x += step->x;
		start->y += sec_step->y;
	}
}

void	ft_bresenham(t_game_object *game_object, int color,
	t_coor start, t_coor end)
{
	t_coor	step;
	t_coor	sec_step;
	t_coor	error;

	step = (t_coor){abs(end.x - start.x), -abs(end.y - start.y)};
	sec_step = (t_coor){1, 1};
	if (start.x > end.x)
		sec_step.x = -1;
	if (start.y > end.y)
		sec_step.y = -1;
	error.x = step.x + step.y;
	while (1)
	{
		ft_put_pixel(game_object, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		ft_calulate_errors(&error, &step, &sec_step, &start);
	}
}
