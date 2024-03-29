/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:30:21 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/10 10:58:00 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_check_next_position(t_game_object *game_object,
		t_d_coor edge, t_d_coor world_position)
{
	t_coor		grid_position;

	grid_position = (t_coor){world_position.x, world_position.y};
	if (!ft_is_position_valid(game_object, (t_coor){edge.x, edge.y}))
	{
		game_object->player.world_position = world_position;
		if (ft_is_position_valid(game_object, (t_coor){round(edge.x), edge.y}))
			game_object->player.world_position.x = grid_position.x + 0.5;
		if (ft_is_position_valid(game_object, (t_coor){edge.x, round(edge.y)}))
			game_object->player.world_position.y = grid_position.y + 0.5;
		if (ft_is_position_valid(game_object,
				(t_coor){round(edge.x - 1), edge.y}))
			game_object->player.world_position.x = grid_position.x + 0.5;
		if (ft_is_position_valid(game_object,
				(t_coor){edge.x, round(edge.y - 1)}))
			game_object->player.world_position.y = grid_position.y + 0.5;
		game_object->player.grid_position = (t_coor)
		{game_object->player.world_position.x,
			game_object->player.world_position.y};
	}
}

void	ft_check_walls(t_game_object *game_object)
{
	t_d_coor	world_position;
	t_d_coor	edge;

	if (ft_get_movement_key(FOREWORD) == 1)
	{
		world_position = ft_add_vector_2d(game_object->player.world_position,
				game_object->player.movement);
		edge = ft_add_vector_2d(game_object->player.world_position,
				ft_scale_vector_2d(game_object->player.movement, 1.4));
		ft_check_next_position(game_object,
			(t_d_coor){edge.x, edge.y}, world_position);
	}
	if (ft_get_movement_key(BACKWARD) == 1)
	{
		world_position = ft_sub_vector_2d(game_object->player.world_position,
				game_object->player.movement);
		edge = ft_add_vector_2d(game_object->player.world_position,
				ft_scale_vector_2d(game_object->player.movement, -1.4));
		ft_check_next_position(game_object,
			(t_d_coor){edge.x, edge.y}, world_position);
	}
}

void	ft_head_tilt(t_game_object *game_object)
{
	t_view	*view;

	view = &game_object->render_data.view_data;
	if (ft_get_movement_key(UP) == 1 && view->vertical_tilt < M_1_PI - 0.05)
	{
		view->vertical_tilt += game_object->player.tilt_step;
		view->view_shift = tan(view->vertical_tilt) * view->view_plane_distance;
		view->half_view_plane = view->half_view_plane_save + view->view_shift;
	}
	if (ft_get_movement_key(DOWN) == 1 && view->vertical_tilt > -M_1_PI + 0.05)
	{
		view->vertical_tilt -= game_object->player.tilt_step;
		view->view_shift = tan(view->vertical_tilt) * view->view_plane_distance;
		view->half_view_plane = view->half_view_plane_save + view->view_shift;
	}
}

void	ft_movement(t_game_object *game_object)
{
	if (ft_get_movement_key(LEFT) == 1 || ft_get_movement_key(RIGHT) == 1)
	{
		if (ft_get_movement_key(LEFT) == 1)
			game_object->player.orientation -= game_object->player.rot_step;
		if (ft_get_movement_key(RIGHT) == 1)
			game_object->player.orientation += game_object->player.rot_step;
		game_object->player.orientation = ft_check_angle(
				game_object->player.orientation);
		game_object->player.movement = ft_scale_vector_2d(
				ft_normalise_vector_2d(
					ft_angle_to_2d_vector
					(ft_check_angle(game_object->player.orientation))),
				game_object->player.step);
	}
	if (ft_get_movement_key(FOREWORD) == 1
		|| ft_get_movement_key(BACKWARD) == 1)
		ft_check_walls(game_object);
}

void	ft_run(t_game_object *game_object)
{
	if (ft_get_movement_key(SHIFT) == 1
		&& !game_object->player.is_running)
	{
		game_object->player.step += 0.6;
		game_object->player.is_running = 1;
	}
	if (ft_get_movement_key(SHIFT) == 0
		&& game_object->player.is_running)
	{
		game_object->player.step -= 0.6;
		game_object->player.is_running = 0;
	}
}
