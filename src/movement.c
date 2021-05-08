/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:30:21 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/06 23:54:06 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_check_walls(t_game_object *game_object)
{
	t_d_coor	world_position;
	t_d_coor	edge;
	t_coor		grid_position;

	world_position = game_object->player.world_position;
	if (get_movement_key(FOREWORD) == 1)
		world_position = (t_d_coor){world_position.x
			+ game_object->player.movement.x,
			world_position.y + game_object->player.movement.y};
	if (get_movement_key(BACKWARD) == 1)
		world_position = (t_d_coor){world_position.x
			- game_object->player.movement.x,
			world_position.y - game_object->player.movement.y};
	edge = ft_add_vector2D(world_position,
			ft_scale_vector2D(
				ft_normalise_vector2D(game_object->player.movement), 0.5));
	grid_position = (t_coor){world_position.x, world_position.y};
	if (!is_position_valid(game_object, (t_coor){edge.x, edge.y}))
	{
		game_object->player.world_position = world_position;
		game_object->player.grid_position = grid_position;
	}
}

void	ft_head_tilt(t_game_object *game_object)
{
	t_view	*view;

	view = &game_object->render_data.view_data;
	if (get_movement_key(UP) == 1 && view->vertical_tilt < M_PI_4)
	{
		view->vertical_tilt += 0.05;
		view->view_shift = tan(view->vertical_tilt) * view->view_plane_distance;
		view->half_view_plane = view->half_view_plane_save + view->view_shift;
	}
	if (get_movement_key(DOWN) == 1 && view->vertical_tilt > -M_PI_4)
	{
		view->vertical_tilt -= 0.05;
		view->view_shift = tan(view->vertical_tilt) * view->view_plane_distance;
		view->half_view_plane = view->half_view_plane_save + view->view_shift;
	}
}

void	ft_movement(t_game_object *game_object)
{
	if (get_movement_key(LEFT) == 1 || get_movement_key(RIGHT) == 1)
	{
		if (get_movement_key(LEFT) == 1)
			game_object->player.orientation -= .1;
		if (get_movement_key(RIGHT) == 1)
			game_object->player.orientation += .1;
		game_object->player.orientation = ft_check_angle(
				game_object->player.orientation);
		game_object->player.movement = ft_scale_vector2D(
				ft_angleToVector2D(game_object->player.orientation),
				game_object->player.step);
	}
	if (get_movement_key(FOREWORD) == 1 || get_movement_key(BACKWARD) == 1)
		ft_check_walls(game_object);
}

void	ft_run(t_game_object *game_object)
{
	if (get_movement_key(SHIFT) == 1
		&& !game_object->player.is_running)
	{
		game_object->player.step += 0.6;
		game_object->player.movement = ft_scale_vector2D(
				ft_angleToVector2D(game_object->player.orientation),
				game_object->player.step);
		game_object->player.is_running = 1;
	}
	if (get_movement_key(SHIFT) == 0
		&& game_object->player.is_running)
	{
		game_object->player.step -= 0.6;
		game_object->player.movement = ft_scale_vector2D(
				ft_angleToVector2D(game_object->player.orientation),
				game_object->player.step);
		game_object->player.is_running = 0;
	}
}
