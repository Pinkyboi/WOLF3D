/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_constructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 19:34:44 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/29 19:34:45 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_calculate_map_props(t_game_object *game_object)
{
	double	radius;

	if (game_object->render_data.window_resolution.y
		> game_object->render_data.window_resolution.x)
		radius = game_object->render_data.window_resolution.x / 8;
	else
		radius = game_object->render_data.window_resolution.y / 8;
	game_object->min_map.total_radius = ft_clip_max(100, radius);
	game_object->min_map.ring_size = game_object->min_map.total_radius / 8.0;
	game_object->min_map.radius = game_object->min_map.total_radius
		- game_object->min_map.ring_size;
	game_object->min_map.block_size = game_object->min_map.radius / 8;
	game_object->min_map.player_size
		= (int)((double)game_object->min_map.block_size / 2.0);
	game_object->min_map.center_position
		= (t_d_coor){game_object->min_map.total_radius
		+ game_object->min_map.ring_size,
		game_object->render_data.window_resolution.y
		- game_object->min_map.total_radius
		- game_object->min_map.ring_size};
}
