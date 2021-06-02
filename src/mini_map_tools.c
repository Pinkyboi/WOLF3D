/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 20:39:27 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/29 20:39:28 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_draw_disk(t_game_object *game_object, int radius,
	int color, t_d_coor center)
{
	t_d_coor	index;
	t_d_coor	max_index;

	index = ft_sub_vector2D(center, (t_d_coor){radius, radius});
	max_index = ft_add_vector2D(index, (t_d_coor){radius, radius});
	while (index.y <= max_index.y + radius)
	{
		index.x = center.x - radius;
		while (index.x <= max_index.x + radius)
		{
			if (ft_size_vector2D(ft_sub_vector2D(index, center)) <= radius)
				ft_put_pixel(game_object, (t_coor){index.x, index.y}, color);
			index.x++;
		}
		index.y++;
	}
}

void	ft_print_fov(t_game_object *game_object, t_d_coor center,
	int ray_number, int size)
{
	double		anglar_step;
	double		ray_index;
	double		max_index;
	t_d_coor	edge;

	ray_index = game_object->player.orientation - PLAYER_FOV / 2;
	max_index = ray_index + PLAYER_FOV;
	anglar_step = (max_index - ray_index) / (double)ray_number;
	while (ray_index <= max_index)
	{
		edge = ft_sub_vector2D(center,
				ft_scale_vector2D(ft_angleToVector2D(ray_index), size));
		ft_bresenham(game_object, MAP_PLAYER_COLOR,
			(t_coor){center.x, center.y}, (t_coor){edge.x, edge.y});
		ray_index += anglar_step;
	}
}
