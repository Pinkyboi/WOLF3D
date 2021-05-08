/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/07 22:40:44 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_textured_render(t_game_object *game_object)
{
	t_render		render_data;
	t_block_list	*current_block;

	current_block = game_object->current_block;
	if (game_object->current_block)
	{
		render_data = game_object->current_block->render.render_data;
		current_block->render.render_function(game_object, render_data);
	}
}

void	ft_ray_shooter(t_game_object *game_object)
{
	double		step;
	double		first_angle;
	t_render	render_data;

	step = PLAYER_FOV / game_object->render_data.window_resolution.x;
	first_angle = game_object->player.orientation - (PLAYER_FOV / 2);
	game_object->drawing_index.x = -1;
	while (++game_object->drawing_index.x
		< game_object->render_data.window_resolution.x)
	{
		game_object->ray_data.hit_distance = 0;
		game_object->current_block = NULL;
		first_angle = ft_check_angle(first_angle);
		game_object->ray_data.current_ray = ft_angleToVector2D(first_angle);
		ft_define_check_step(game_object);
		game_object->ray_data.straight_distance
			= game_object->ray_data.hit_distance;
		game_object->ray_data.straight_distance *= (double)BLOCK_SIZE;
		game_object->ray_data.straight_distance
			*= cos(game_object->player.orientation - first_angle);
		game_object->ray_data.angle = first_angle;
		game_object->render_data.render_function(game_object);
		first_angle += step;
	}
}
