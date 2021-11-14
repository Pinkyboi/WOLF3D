/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/14 19:07:57 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_get_texture_x_coor(t_game_object *game_object, t_texture texture)
{
	double		wall_index;
	int			texture_index;
	t_d_coor	end;

	end = ft_add_vector_2d(game_object->player.world_position,
			ft_scale_vector_2d(game_object->ray_data.current_ray,
				game_object->ray_data.hit_distance));
	wall_index = end.x;
	if (game_object->ray_data.hit_type == 'V')
		wall_index = end.y;
	wall_index -= (int)wall_index;
	texture_index = wall_index * (double)texture.texture_width;
	if (game_object->ray_data.hit_type == 'V'
		&& game_object->ray_data.current_ray.x > 0)
		texture_index = texture.texture_width - texture_index - 1;
	if (game_object->ray_data.hit_type == 'H'
		&& game_object->ray_data.current_ray.y < 0)
		texture_index = texture.texture_width - texture_index - 1;
	return (texture_index);
}

void	ft_draw_texture_line(t_coor edges,
	t_game_object *game_object, t_render data, double shade)
{
	t_d_coor	step;
	int			min_edge;
	double		texture_index;
	int			color;

	step.y = (double)data.texture.texture_height / (edges.y - edges.x + 1);
	step.x = ft_get_texture_x_coor(game_object, data.texture);
	min_edge = ft_clip_min(0, edges.x);
	texture_index = 0;
	if (edges.x < 0)
		texture_index = (min_edge - edges.x) * step.y;
	edges.y = ft_clip_max(game_object->render_data.window_resolution.y,
			edges.y);
	edges.x = min_edge - 1;
	while (++edges.x <= edges.y)
	{
		color = ft_get_pixel(&data.texture, (t_coor){(int)step.x,
				(int)texture_index});
		color = ft_scale_color_int(color, shade);
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x, edges.x}, color);
		texture_index += step.y;
	}
}

void	ft_texture_wall(t_game_object *game_object, t_render data)
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
	shade = 0.9;
	if (game_object->ray_data.hit_type == 'V')
		shade = 0.8;
	if (game_object->player.view_distance > 0)
		shade = ft_clip_min_max(0, 1, game_object->player.view_distance
				/ game_object->ray_data.straight_distance);
	ft_draw_texture_line((t_coor){start, end},
		game_object, data, shade);
	ft_tile_render(game_object, (t_coor){0, start}, 'C');
	ft_tile_render(game_object, (t_coor){end,
		game_object->render_data.window_resolution.y}, 'F');
}
