/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameobject_constructor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:35:15 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/08 19:04:04 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*ft_get_argument(char *argument_name, char *default_value,
	t_argument_list *argument_list)
{
	t_argument_list	*wanted_node;

	wanted_node = ft_find_argument_node(argument_list, argument_name);
	if (wanted_node)
		return (wanted_node->argument_value);
	return (default_value);
}

void	ft_default_player_arg(t_game_object *game_object)
{
	game_object->player.orientation = 0.01;
	game_object->player.step = 0.4;
	game_object->player.tilt_step = 0.05;
	game_object->player.movement = ft_normalise_vector_2d(
			ft_scale_vector_2d(
				ft_angle_to_2d_vector(game_object->player.orientation),
				game_object->player.step));
	game_object->player.height = (double)BLOCK_SIZE / 2.0;
}

void	ft_load_player_data(t_game_object *game_object, char *argument_block)
{
	t_coor	position;

	game_object->parser.current_arguments = ft_create_argument_list(
			argument_block, NULL, PLAYER_TAG);
	ft_default_player_arg(game_object);
	position = ft_parse_coordinate(ft_get_argument("Position", "(0,0)",
				game_object->parser.current_arguments));
	game_object->player.grid_position
		= (t_coor){position.x + 1, position.y + 1};
	game_object->player.world_position.x = .5
		+ game_object->player.grid_position.x;
	game_object->player.world_position.y = .5
		+ game_object->player.grid_position.y;
	game_object->player.hp = ft_parse_counters(ft_get_argument("Health",
				"100", game_object->parser.current_arguments), MIN_HP, MAX_HP);
	game_object->player.stamina = ft_parse_counters(
			ft_get_argument("Stamina", "100",
				game_object->parser.current_arguments),
			MIN_STAMINA, MAX_STAMINA);
	game_object->player.view_distance
		= ft_parse_counters(ft_get_argument("View_distance", "0",
				game_object->parser.current_arguments), 0, INT32_MAX);
	ft_free_argument_list(game_object->parser.current_arguments);
	free(argument_block);
}
