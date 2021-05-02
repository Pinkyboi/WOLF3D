/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_elements_constructor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:35:15 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/29 13:35:23 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char	*get_argument(char *argument_name, char *default_value,
	t_argument_list *argument_list)
{
	t_argument_list	*wanted_node;

	wanted_node = search_for_argument_node(argument_list, argument_name);
	if (wanted_node)
		return (wanted_node->argument_value);
	return (default_value);
}

void	load_render_data(t_game_object *game_object, char *agrument_block)
{
	game_object->current_arguments = create_argument_list(agrument_block,
			NULL, ENV_TAG);
	game_object->render_data.render_function = parse_render_type(
			get_argument("type", "Basic", game_object->current_arguments));
	game_object->render_data.window_resolution = parse_resolution(
			get_argument("resolution", "Basic",
				game_object->current_arguments));
	game_object->render_data.north_wall = parse_render(get_argument("N",
				NORTH_COLOR, game_object->current_arguments));
	game_object->render_data.south_wall = parse_render(get_argument("S",
				SOUTH_COLOR, game_object->current_arguments));
	game_object->render_data.south_wall = parse_render(get_argument("E",
				EAST_COLOR, game_object->current_arguments));
	game_object->render_data.west_wall = parse_render(get_argument("W",
				WEST_COLOR, game_object->current_arguments));
	free_argument_list(game_object->current_arguments);
}

void	load_player_data(t_game_object *game_object, char *agrument_block)
{
	game_object->current_arguments = create_argument_list(
			agrument_block, NULL, PLAYER_TAG);
	game_object->player.grid_postion = parse_coordinate(
			get_argument("position", "(0,0)", game_object->current_arguments));
	game_object->player.hp = parse_counters(get_argument("health", "100",
				game_object->current_arguments), MIN_HP, MAX_HP);
	game_object->player.stamina = parse_counters(get_argument("stamina", "100",
				game_object->current_arguments), MIN_STAMINA, MAX_STAMINA);
	free_argument_list(game_object->current_arguments);
}
