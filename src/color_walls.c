/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/07 22:09:58 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_basic_render(t_game_object *game_object)
{
	if (game_object->ray_data.hit_type == 'H')
	{
		if (game_object->ray_data.current_ray.y > 0)
			game_object->render_data.south_wall.render_function(game_object,
				game_object->render_data.south_wall.render_data);
		else
			game_object->render_data.north_wall.render_function(game_object,
				game_object->render_data.north_wall.render_data);
	}
	else
	{
		if (game_object->ray_data.current_ray.x > 0)
			game_object->render_data.east_wall.render_function(game_object,
				game_object->render_data.east_wall.render_data);
		else
			game_object->render_data.west_wall.render_function(game_object,
				game_object->render_data.west_wall.render_data);
	}
}

void	ft_draw_hard_line(int start, int end, int color,
	t_game_object *game_object)
{
	start = ft_clip_min_max(0,
			game_object->render_data.window_resolution.y, start);
	end = ft_clip_min_max(0,
			game_object->render_data.window_resolution.y, end);
	while (start <= end)
	{
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x, start}, color);
		start++;
	}	
}

void	color_wall(t_game_object *game_object, t_render data)
{
	double	wall_size;
	int		start;
	int		end;

	wall_size = (int)(game_object->render_data.view_data.view_plane_distance
			* BLOCK_SIZE / (game_object->ray_data.straight_distance));
	start = (game_object->render_data.view_data.half_view_plane
			- (wall_size / 2));
	end = start + wall_size;
	tile_render(game_object, (t_coor){0, start}, 'C');
	tile_render(game_object,
		(t_coor){end, game_object->render_data.window_resolution.y}, 'F');
	ft_draw_hard_line(start, end, data.color, game_object);
}
