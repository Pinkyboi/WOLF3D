/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/07 22:27:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_get_textureX_coor(t_game_object *game_object, t_texture texture)
{
	double		wall_index;
	int			texture_index;
	t_d_coor	end;

	end = ft_add_vector2D(game_object->player.world_position,
			ft_scale_vector2D(game_object->ray_data.current_ray,
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

void	ft_draw_texture_line(t_coor edges, int wall_size,
	t_game_object *game_object, t_render data)
{
	t_d_coor	step;
	double		texture_index;
	int			color;

	texture_index = 0;
	step.y = (double)data.texture.texture_height / (wall_size + 1);
	step.x = ft_get_textureX_coor(game_object, data.texture);
	while (edges.x <= edges.y)
	{
		color = data.texture.texture_data[(int)((int)texture_index
				* data.texture.texture_width + (int)(step.x))];
		if (game_object->ray_data.hit_type == 'V')
			color = ft_scale_color_int(color, 0.8);
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x, edges.x}, color);
		texture_index += step.y;
		edges.x++;
	}
}

void	texture_wall(t_game_object *game_object, t_render data)
{
	int		start;
	int		end;
	double	wall_size;

	wall_size = (int)(game_object->render_data.view_data.view_plane_distance
			* BLOCK_SIZE / game_object->ray_data.straight_distance);
	start = game_object->render_data.view_data.half_view_plane
		- (wall_size / 2);
	end = start + wall_size;
	tile_render(game_object, (t_coor){0, start}, 'C');
	tile_render(game_object, (t_coor){end,
		game_object->render_data.window_resolution.y}, 'F');
	ft_draw_texture_line((t_coor){start, end}, wall_size, game_object, data);
}
