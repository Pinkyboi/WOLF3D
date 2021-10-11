/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/20 20:27:39 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_basic_render(t_game_object *game_object)
{
	if (game_object->ray_data.hit_type == 'H')
	{
		if (game_object->ray_data.current_ray.y > 0)
			game_object->render_data.basic_render.
				south_wall.render_function(game_object,
				game_object->render_data.basic_render.south_wall.render_data);
		else
			game_object->render_data.basic_render.
				north_wall.render_function(game_object,
				game_object->render_data.basic_render.north_wall.render_data);
	}
	else
	{
		if (game_object->ray_data.current_ray.x > 0)
			game_object->render_data.basic_render.
				east_wall.render_function(game_object,
				game_object->render_data.basic_render.east_wall.render_data);
		else
			game_object->render_data.basic_render.west_wall.
				render_function(game_object,
				game_object->render_data.basic_render.west_wall.render_data);
	}
}

void	ft_draw_hard_line(t_coor edge, int color,
	t_game_object *game_object, double shade)
{
	edge.x = ft_clip_min_max(0,
			game_object->render_data.window_resolution.y, edge.x);
	edge.y = ft_clip_min_max(0,
			game_object->render_data.window_resolution.y, edge.y);
	color = ft_scale_color_int(color, shade);
	while (edge.x <= edge.y)
	{
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x, edge.x}, color);
		edge.x++;
	}	
}

void	ft_color_wall(t_game_object *game_object, t_render data)
{
	double	wall_size;
	double	shade;
	int		start;
	int		end;

	wall_size = (int)(game_object->render_data.view_data.view_plane_distance
			* BLOCK_SIZE / (game_object->ray_data.straight_distance));
	start = (game_object->render_data.view_data.half_view_plane
			- (wall_size / 2));
	end = start + wall_size;
	shade = 0.9;
	if (game_object->ray_data.hit_type == 'V')
		shade = 0.8;
	if (game_object->player.view_distance > 0)
		shade = ft_clip_min_max(0, 1, game_object->player.view_distance
				/ game_object->ray_data.straight_distance);
	ft_tile_render(game_object, (t_coor){0, start}, 'C');
	ft_tile_render(game_object,
		(t_coor){end, game_object->render_data.window_resolution.y}, 'F');
	ft_draw_hard_line((t_coor){start, end}, data.color, game_object, shade);
}
