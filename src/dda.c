/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:55:21 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/03 14:55:23 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_setup_dda(t_game_object *game_object, t_d_coor *rayStep,
	t_d_coor *rayDistance, t_coor *gridStep)
{
	t_d_coor	ray;

	ray = ft_normalise_vector2D(game_object->ray_data.current_ray);
	ft_get_right_step(ray, rayStep);
	if (ray.x < 0)
		rayDistance->x = (game_object->player.world_position.x
				- (float)game_object->player.grid_position.x) * rayStep->x;
	else
		rayDistance->x = ((game_object->player.grid_position.x + 1.0)
				- game_object->player.world_position.x) * rayStep->x;
	if (ray.y < 0)
		rayDistance->y = (game_object->player.world_position.y
				- (float)game_object->player.grid_position.y) * rayStep->y;
	else
		rayDistance->y = ((game_object->player.grid_position.y + 1.0)
				- game_object->player.world_position.y) * rayStep->y;
	*gridStep = ft_get_sign(ray);
}

void	ft_dda(t_game_object *game_object, t_d_coor *rayStep,
	t_d_coor *rayDistance, t_coor *gridStep)
{
	t_coor		ray_grid_position;

	ray_grid_position = game_object->player.grid_position;
	while (game_object->ray_data.hit_distance < MAX_DIST)
	{
		if (rayDistance->x < rayDistance->y)
		{
			ray_grid_position.x += gridStep->x;
			game_object->ray_data.hit_distance = rayDistance->x;
			game_object->ray_data.hit_type = 'V';
			rayDistance->x += rayStep->x;
		}
		else
		{
			ray_grid_position.y += gridStep->y;
			game_object->ray_data.hit_distance = rayDistance->y;
			game_object->ray_data.hit_type = 'H';
			rayDistance->y += rayStep->y;
		}
		if (ft_is_block_solid(game_object, ray_grid_position))
			break ;
	}
}

void	ft_define_check_step(t_game_object *game_object)
{
	t_coor		gridStep;
	t_d_coor	rayStep;
	t_d_coor	rayDistance;

	ft_setup_dda(game_object, &rayStep, &rayDistance, &gridStep);
	ft_dda(game_object, &rayStep, &rayDistance, &gridStep);
}
