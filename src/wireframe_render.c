/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:09:34 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/31 16:09:36 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_get_wire_color(t_d_coor hit_index, t_game_object *game_object)
{
	if ((hit_index.x >= 0 && hit_index.x <= 0.02)
		|| (hit_index.x >= 0.98 && hit_index.x <= 1))
		return (game_object->render_data.wire_render.edge_color);
	if ((hit_index.y >= 0 && hit_index.y <= 0.02)
		|| (hit_index.y >= 0.98 && hit_index.y <= 1))
		return (game_object->render_data.wire_render.edge_color);
	if ((hit_index.y >= 0.25 - 0.004 && hit_index.y <= 0.25 + 0.004)
		|| (hit_index.y >= 0.5 - 0.004 && hit_index.y <= 0.5 + 0.004)
		|| (hit_index.y >= 0.75 - 0.004 && hit_index.y <= 0.75 + 0.004))
		return (game_object->render_data.wire_render.inner_color);
	if ((hit_index.x >= 0.25 - 0.004 && hit_index.x <= 0.25 + 0.004)
		|| (hit_index.x >= 0.5 - 0.004 && hit_index.x <= 0.5 + 0.004)
		|| (hit_index.x >= 0.75 - 0.004 && hit_index.x <= 0.75 + 0.004))
		return (game_object->render_data.wire_render.inner_color);
	return (game_object->render_data.wire_render.void_color);
}

int	ft_wire_x_color(t_game_object *game_object, double y_index)
{
	double		wall_index;
	t_d_coor	end;

	end = ft_add_vector2D(game_object->player.world_position,
			ft_scale_vector2D(game_object->ray_data.current_ray,
				game_object->ray_data.hit_distance));
	wall_index = end.x;
	if (game_object->ray_data.hit_type == 'V')
		wall_index = end.y;
	wall_index -= (int)wall_index;
	return (ft_get_wire_color((t_d_coor){wall_index, y_index}, game_object));
}

void	ft_draw_wire_line(t_coor edges,
	t_game_object *game_object, double shade)
{
	t_d_coor	step;
	double		texture_index;
	int			color;

	texture_index = 0;
	step.y = 1.0 / (edges.y - edges.x + 1);
	while (edges.x <= edges.y)
	{
		color = ft_wire_x_color(game_object, texture_index);
		color = ft_scale_color_int(color, shade);
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x, edges.x}, color);
		edges.x++;
		texture_index += step.y;
	}
}

void	ft_wireframe_draw(t_game_object *game_object)
{
	int		start;
	int		end;
	double	wall_size;
	double	shade;

	wall_size = (int)(game_object->render_data.view_data.view_plane_distance
			* BLOCK_SIZE / game_object->ray_data.straight_distance);
	start = game_object->render_data.view_data.half_view_plane
		- (wall_size / 2);
	end = start + wall_size;
	shade = 1;
	if (game_object->ray_data.hit_type == 'V')
		shade = 0.8;
	if (game_object->player.view_distance > 0)
		shade = ft_clip_min_max(0, 1, game_object->player.view_distance
				/ game_object->ray_data.straight_distance);
	ft_draw_wire_line((t_coor){start, end},
		game_object, shade);
	ft_wire_tile(game_object, (t_coor){0, start});
	ft_wire_tile(game_object, (t_coor){end,
		game_object->render_data.window_resolution.y});
}
