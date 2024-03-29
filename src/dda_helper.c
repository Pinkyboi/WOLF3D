/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:40:06 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/05 01:07:24 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_coor	ft_get_sign(t_d_coor coor)
{
	t_coor	sign;

	sign = (t_coor){1, 1};
	if (coor.x < 0)
		sign.x = -1;
	if (coor.y < 0)
		sign.y = -1;
	return (sign);
}

void	ft_get_right_step(t_d_coor ray, t_d_coor *ray_step)
{
	if (!ray.x)
		ray_step->x = 0;
	else
		ray_step->x = sqrtf(1 + ft_sqr(ray.y / ray.x));
	if (!ray.y)
		ray_step->y = 0;
	else
		ray_step->y = sqrtf(1 + ft_sqr(ray.x / ray.y));
}

short	ft_is_position_valid(t_game_object *game_object, t_coor grid_position)
{
	if (grid_position.x < 0 || grid_position.y < 0)
		return (-1);
	if (grid_position.x >= game_object->map.map_dimentions.x
		|| grid_position.y >= game_object->map.map_dimentions.y)
		return (-1);
	if (game_object->map.map_grid[grid_position.y][grid_position.x].wall)
		return (1);
	return (0);
}

short	ft_is_block_solid(t_game_object *game_object, t_coor grid_position)
{
	t_block_list	*render_tool;
	short			state;

	state = ft_is_position_valid(game_object, grid_position);
	if (state == 1)
	{
		render_tool = game_object->map.map_grid[grid_position.y]
		[grid_position.x].wall;
		game_object->current_block = render_tool;
	}
	return (state);
}
