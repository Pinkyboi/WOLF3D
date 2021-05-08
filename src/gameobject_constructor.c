/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameobject_constructor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:35:15 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/07 22:40:09 by abenaiss         ###   ########.fr       */
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

void	load_screen_data(t_game_object *game_object)
{
	t_coor	resolution;

	resolution = parse_resolution(get_argument("resolution", "1000 x 1000",
				game_object->parser.current_arguments));
	game_object->render_data.window_resolution = resolution;
	game_object->render_data.view_data.view_plane_distance = resolution.x;
	game_object->render_data.view_data.half_view_plane = resolution.y / 2;
	game_object->render_data.view_data.half_view_plane_save
		= game_object->render_data.view_data.half_view_plane;
	game_object->render_data.view_data.view_shift = 0;
	game_object->render_data.view_data.vertical_tilt = 0;
}

void	load_render_data(t_game_object *game_object, char *agrument_block)
{
	game_object->parser.current_arguments = create_argument_list(agrument_block,
			NULL, ENV_TAG);
	game_object->render_data.render_function = parse_render_type(
			get_argument("type", "Basic",
				game_object->parser.current_arguments));
	load_screen_data(game_object);
	game_object->render_data.north_wall = parse_render(get_argument("N",
				NORTH_COLOR, game_object->parser.current_arguments));
	game_object->render_data.south_wall = parse_render(get_argument("S",
				SOUTH_COLOR, game_object->parser.current_arguments));
	game_object->render_data.east_wall = parse_render(get_argument("E",
				EAST_COLOR, game_object->parser.current_arguments));
	game_object->render_data.west_wall = parse_render(get_argument("W",
				WEST_COLOR, game_object->parser.current_arguments));
	free_argument_list(game_object->parser.current_arguments);
}

void	load_player_data(t_game_object *game_object, char *agrument_block)
{
	t_coor	position;

	game_object->parser.current_arguments = create_argument_list(
			agrument_block, NULL, PLAYER_TAG);
	position = parse_coordinate(get_argument("position", "(0,0)",
				game_object->parser.current_arguments));
	game_object->player.grid_position
		= (t_coor){position.x + 1, position.y + 1};
	game_object->player.world_position.x = .5
		+ game_object->player.grid_position.x;
	game_object->player.world_position.y = .5
		+ game_object->player.grid_position.y;
	game_object->player.hp = parse_counters(get_argument("health",
				"100", game_object->parser.current_arguments), MIN_HP, MAX_HP);
	game_object->player.stamina = parse_counters(get_argument("stamina", "100",
				game_object->parser.current_arguments),
			MIN_STAMINA, MAX_STAMINA);
	game_object->player.orientation = 0.0;
	game_object->player.step = 0.4;
	game_object->player.movement = ft_scale_vector2D(
			ft_angleToVector2D(game_object->player.orientation),
			game_object->player.step);
	game_object->player.height = (double)BLOCK_SIZE / 2.0;
	free_argument_list(game_object->parser.current_arguments);
}
