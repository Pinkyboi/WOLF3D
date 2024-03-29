/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:50:27 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/25 04:21:05 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_check_for_blocks(t_game_object *game_object,
	t_d_coor player_center, t_d_coor center, t_d_coor index)
{
	t_d_coor	position;
	t_d_coor	radial;

	position = (t_d_coor){player_center.x + ((center.x - index.x)
			/ game_object->min_map.block_size),
		player_center.y + ((center.y - index.y)
			/ game_object->min_map.block_size)};
	if (ft_is_position_valid(game_object, (t_coor){position.x, position.y}))
	{
		radial = ft_sub_vector_2d((t_d_coor){index.x,
				index.y}, center);
		if (ft_size_vector_2d(radial) <= game_object->min_map.radius)
			ft_put_pixel(game_object, (t_coor){index.x,
				index.y}, MAP_BLOCK_COLOR);
	}
}

void	ft_mini_map_blocks(t_game_object *game_object,
			int radius, t_d_coor center)
{
	t_d_coor	index;
	t_d_coor	player_center;
	t_d_coor	max_index;

	player_center = (t_d_coor){game_object->player.grid_position.x,
		game_object->player.grid_position.y};
	index = (t_d_coor){center.x - radius, center.y - radius};
	max_index = ft_add_vector_2d(index, (t_d_coor){2 * radius, 2 * radius});
	while (index.y <= max_index.y)
	{
		index.x = center.x - radius;
		while (index.x <= max_index.x)
		{
			ft_check_for_blocks(game_object,
				player_center, center, index);
			index.x++;
		}
		index.y++;
	}
}

void	ft_print_mini_map(t_game_object *game_object, t_d_coor center)
{
	double		radius;
	t_d_coor	player_center;

	radius = game_object->min_map.total_radius;
	player_center = (t_d_coor){game_object->player.grid_position.x,
		game_object->player.grid_position.y};
	ft_draw_disk(game_object, radius, MAP_RING_COLOR, center);
	ft_draw_disk(game_object, game_object->min_map.radius,
		MAP_VOID_COLOR, center);
	ft_print_fov(game_object, center, 30, game_object->min_map.block_size);
	ft_draw_disk(game_object, game_object->min_map.player_size,
		MAP_PLAYER_COLOR, center);
	ft_mini_map_blocks(game_object,
		game_object->min_map.radius, center);
}
