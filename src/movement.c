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

int 		ft_check_walls(t_game_object *game_object, int key)
{
	t_d_coor world_position;
	t_d_coor edge;
	t_coor 	grid_position;

	world_position = game_object->player.world_position;
	if(key == FOREWORD)
		world_position = (t_d_coor){world_position.x +
			game_object->player.movement.x,
			world_position.y + game_object->player.movement.y};
	if(key == BACKWARD)
		world_position = (t_d_coor){world_position.x -
			game_object->player.movement.x,
			world_position.y - game_object->player.movement.y};
	edge = ft_add_vector2D(world_position,
		ft_scale_vector2D(ft_normalise_vector2D(game_object->player.movement), 0.5));
	grid_position = (t_coor){world_position.x ,world_position.y};
	if(!is_position_valid(game_object, (t_coor){edge.x, edge.y}))
	{
		game_object->player.world_position = world_position;
		game_object->player.grid_position = grid_position;
		return (1);
	}
	return(0);
}

void 		ft_movement(int key, t_game_object *game_object)
{
	if(key == RIGHT || key == LEFT)
	{
		if(key == LEFT)
			game_object->player.orientation -= .1;
		if(key == RIGHT)
			game_object->player.orientation += .1;
		game_object->player.orientation = ft_check_angle(game_object->player.orientation);
		game_object->player.movement = ft_scale_vector2D(
		ft_angleToVector2D(game_object->player.orientation),
			game_object->player.step);
	}
	if(key == FOREWORD && ft_check_walls(game_object, key))
	{
		game_object->player.world_position = ft_add_vector2D(game_object->player.world_position,
									game_object->player.movement);
		game_object->player.grid_position = (t_coor){game_object->player.world_position.x,
										game_object->player.world_position.y};
	}
	if(key == BACKWARD && ft_check_walls(game_object, key))
	{
		game_object->player.world_position = ft_sub_vector2D(game_object->player.world_position,
									game_object->player.movement);
		game_object->player.grid_position =(t_coor){game_object->player.world_position.x,
										game_object->player.world_position.y};
	}	
}