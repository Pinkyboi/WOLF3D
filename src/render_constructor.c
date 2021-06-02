/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_constructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:05:25 by abenaiss          #+#    #+#             */
/*   Updated: 2021/06/01 19:05:27 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_load_screen_data(t_game_object *game_object)
{
	t_coor	resolution;

	resolution = ft_parse_resolution(
			ft_get_argument("Resolution", "1000 x 1000",
				game_object->parser.current_arguments));
	game_object->render_data.window_resolution = resolution;
	game_object->render_data.view_data.view_plane_distance = resolution.x;
	game_object->render_data.view_data.half_view_plane = resolution.y / 2;
	game_object->render_data.view_data.half_view_plane_save
		= game_object->render_data.view_data.half_view_plane;
	game_object->render_data.view_data.view_shift = 0;
	game_object->render_data.view_data.vertical_tilt = 0;
	ft_calculate_map_props(game_object);
}

void	ft_load_basic_render(t_game_object *game_object,
	t_render_data *render_data)
{
	render_data->basic_render.north_wall = ft_parse_render(
			ft_get_argument("North",
				NORTH_COLOR, game_object->parser.current_arguments));
	render_data->basic_render.south_wall = ft_parse_render(
			ft_get_argument("South",
				SOUTH_COLOR, game_object->parser.current_arguments));
	render_data->basic_render.east_wall = ft_parse_render(
			ft_get_argument("East",
				EAST_COLOR, game_object->parser.current_arguments));
	render_data->basic_render.west_wall = ft_parse_render(
			ft_get_argument("West",
				WEST_COLOR, game_object->parser.current_arguments));
}

int	parse_color(char *render_argument)
{
	int	color;

	if (!ft_stock_hex(render_argument, &color))
		ft_err_print("wrong color format in:", render_argument);
	return (color);
}

void	ft_load_wireframe_render(t_game_object *game_object,
	t_render_data *render_data)
{
	render_data->wire_render.void_color = parse_color(
			ft_get_argument("Main_color",
				WIRE_MAIN_COLOR, game_object->parser.current_arguments));
	render_data->wire_render.edge_color = parse_color(
			ft_get_argument("Edge_color",
				WIRE_EDGE_COLOR, game_object->parser.current_arguments));
	render_data->wire_render.inner_color = parse_color(
			ft_get_argument("Inner_color",
				WIRE_INNER_COLOR, game_object->parser.current_arguments));
}

void	ft_load_render_data(t_game_object *game_object, char *agrument_block)
{
	game_object->parser.current_arguments = ft_create_argument_list(
			agrument_block,
			NULL, ENV_TAG);
	game_object->render_data.render_function = ft_parse_render_type(
			ft_get_argument("Type", "Basic",
				game_object->parser.current_arguments));
	ft_load_screen_data(game_object);
	ft_load_basic_render(game_object, &game_object->render_data);
	ft_load_wireframe_render(game_object, &game_object->render_data);
	game_object->render_data.skybox.sky = ft_parse_sky_render(
			ft_get_argument("Sky",
				SKY_COLOR, game_object->parser.current_arguments),
			game_object);
	ft_free_argument_list(game_object->parser.current_arguments);
}
