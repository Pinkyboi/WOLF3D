/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe_tiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 18:56:15 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/31 18:56:16 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/**
 * tile_arg.x : tile distance from the player.
 * tile_arg.y : angle between the player and the tile.
**/

int	get_ft_wire_tile_color(t_game_object *game_object,
		t_d_coor tile_arg)
{
	t_d_coor		texture_ratio;
	t_coor			tile_coor;

	texture_ratio.y = game_object->player.world_position.y
		+ (tile_arg.x * sin(tile_arg.y));
	texture_ratio.x = game_object->player.world_position.x
		+ (tile_arg.x * cos(tile_arg.y));
	tile_coor = (t_coor){(int)texture_ratio.x, (int)texture_ratio.y};
	texture_ratio.x -= tile_coor.x;
	texture_ratio.y -= tile_coor.y;
	return (ft_get_wire_color(texture_ratio, game_object));
}

void	ft_wire_tile(t_game_object *game_object, t_coor range)
{
	double	wall_ratio;
	double	angle;
	double	distance;
	double	shade;
	int		color;

	while (range.x <= range.y)
	{
		wall_ratio = abs(range.x
				- game_object->render_data.view_data.half_view_plane);
		angle = game_object->ray_data.angle;
		distance = game_object->player.height / wall_ratio
			* game_object->render_data.view_data.view_plane_distance
			/ cos(game_object->player.orientation - angle) / (double)BLOCK_SIZE;
		shade = 1;
		if (game_object->player.view_distance > 0)
			shade = ft_clip_min_max(0, 1, game_object->player.view_distance
					/ (distance * (double)BLOCK_SIZE));
		color = get_ft_wire_tile_color(game_object,
				(t_d_coor){distance, angle});
		color = ft_scale_color_int(ft_scale_color_int(color, 0.7), shade);
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x, range.x}, color);
		range.x++;
	}
}
