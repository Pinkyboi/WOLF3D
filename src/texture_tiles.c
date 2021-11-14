/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_tiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 16:44:34 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/10 11:12:21 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	texture_pixel(t_render data, double shade)
{
	int			color;
	t_d_coor	coordinates;

	coordinates = data.texture.coordinates;
	color = ft_get_pixel(&data.texture, (t_coor){coordinates.x, coordinates.y});
	color = ft_scale_color_int(color, 0.7);
	color = ft_scale_color_int(color, shade);
	return (color);
}

int	color_pixel(t_render data, double shade)
{
	int	color;

	color = ft_scale_color_int(data.color, 0.7);
	color = ft_scale_color_int(color, shade);
	return (color);
}

t_block_list	*get_tile_data(t_coor tile_coor,
	t_game_object *game_object, char type)
{
	t_block_list	*render_tool;

	render_tool = NULL;
	if (!ft_is_position_valid(game_object, tile_coor))
	{
		if (type == 'C')
		{
			if (game_object->map.map_grid[tile_coor.y][tile_coor.x].ceiling)
				render_tool = game_object->map.map_grid[tile_coor.y]
				[tile_coor.x].ceiling;
		}
		else if (game_object->map.map_grid[tile_coor.y][tile_coor.x].floor)
			render_tool = game_object->map.map_grid[tile_coor.y]
			[tile_coor.x].floor;
	}
	return (render_tool);
}

/**
 * tile_arg.x : tile distance from the player.
 * tile_arg.y : angle between the player and the tile.
**/

int	get_tile_position(t_game_object *game_object,
		t_d_coor tile_arg, char type, double shade)
{
	t_d_coor		texture_ratio;
	t_coor			tile_coor;
	t_block_list	*block;

	texture_ratio.y = game_object->player.world_position.y
		+ (tile_arg.x * sin(tile_arg.y));
	texture_ratio.x = game_object->player.world_position.x
		+ (tile_arg.x * cos(tile_arg.y));
	tile_coor = (t_coor){(int)texture_ratio.x, (int)texture_ratio.y};
	block = get_tile_data(tile_coor, game_object, type);
	if (block)
	{
		if (block->render.render_function == &ft_texture_wall)
		{
			texture_ratio.x -= tile_coor.x;
			texture_ratio.y -= tile_coor.y;
			texture_ratio.x *= block->render.render_data.texture.texture_width;
			texture_ratio.y *= block->render.render_data.texture.texture_height;
			block->render.render_data.texture.coordinates = texture_ratio;
			return (texture_pixel(block->render.render_data, shade));
		}
		return (color_pixel(block->render.render_data, shade));
	}	
	return (-1);
}

/*
	** hit_info[0] = angle;
	** hit_info[1] = distance;
*/
void	ft_tile_render(t_game_object *game_object, t_coor range, char type)
{
	double	hit_info[2];
	double	shade;
	int		color;

	range.x = ft_clip_min(0, range.x) - 1;
	range.y
		= ft_clip_max(game_object->render_data.window_resolution.y, range.y);
	while (++range.x < range.y)
	{
		hit_info[1] = game_object->ray_data.angle;
		hit_info[0] = game_object->player.height / (abs(range.x
					- game_object->render_data.view_data.half_view_plane))
			* game_object->render_data.view_data.view_plane_distance
			/ cos(game_object->player.orientation
				- hit_info[1]) / (double)BLOCK_SIZE;
		shade = 1;
		if (game_object->player.view_distance > 0)
			shade = ft_clip_min_max(0, 1, game_object->player.view_distance
					/ (hit_info[0] * (double)BLOCK_SIZE));
		color = get_tile_position(game_object,
				(t_d_coor){hit_info[0], hit_info[1]}, type, shade);
		if (color != -1)
			ft_put_pixel(game_object,
				(t_coor){game_object->drawing_index.x, range.x}, color);
	}
}
