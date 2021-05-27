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

double	ft_size_vector2D(t_d_coor vector2D)
{
	return (sqrt(FT_SQR(vector2D.x) + FT_SQR(vector2D.y)));
}

void		ft_draw_block(t_game_object *game_object,t_d_coor position, int size, int color)
{
	int i = -1;
    position = ft_sub_vector2D(position, (t_d_coor){size, size});
	while(++i < size)
	{
		int j = -1;
		while(++j < size)
			ft_put_pixel(game_object, (t_coor){position.x + j, position.y + i},color);
	}
}

void draw_disk(t_game_object *game_object, int radius, int color, t_d_coor center)
{
    t_d_coor index;
    t_d_coor max_index;

    index = ft_sub_vector2D(center, (t_d_coor){radius, radius});
    max_index = ft_add_vector2D(index, (t_d_coor){radius, radius});
    while(index.y <= max_index.y + radius)
    {
        index.x = center.x - radius;
        while(index.x <= max_index.x + radius)
        {
            if(ft_size_vector2D(ft_sub_vector2D(index, center)) <= radius)
                ft_put_pixel(game_object, (t_coor){index.x, index.y}, color);
            index.x++;
        }
        index.y++;
    }
}

t_d_coor	ft_rotate_vector2D(t_d_coor a, double angle)
{
	t_d_coor	result;

	result.x = a.x * cos(angle) - a.y * sin(angle);
	result.y = a.x * sin(angle) + a.y * cos(angle);
	return (result);
}

void		ft_print_coordinate(t_coor position)
{
	printf("(%d, %d)\n", position.x, position.y);
}
void print_mini_map(t_game_object *game_object, int radius, int block_size, t_d_coor center)
{
    t_d_coor index;
    t_d_coor player_center;
    t_d_coor max_index;

    radius *= block_size;
    player_center = (t_d_coor){game_object->player.grid_position.x,
        game_object->player.grid_position.y};

    draw_disk(game_object, radius, 0, center);
    draw_disk(game_object, radius + 10, 0, center);
    draw_disk(game_object, 5, 0xFF0000, center);
    index = (t_d_coor){center.x - radius, center.y - radius};
    max_index = ft_add_vector2D(index, (t_d_coor){radius, radius});  
    while(index.y <= max_index.y + radius)
    {
        index.x = center.x - radius;
        while(index.x <= max_index.x + radius)
        {
            t_d_coor position;
            t_d_coor radial;

            position = (t_d_coor){player_center.x + ((center.x - index.x ) / block_size),
            player_center.y + ((center.y - index.y) / block_size)};
            if (is_position_valid(game_object, (t_coor){position.x, position.y}))
            {
                radial = ft_sub_vector2D((t_d_coor){index.x,
                                index.y}, center);
                if(ft_size_vector2D(radial) <= radius)
                        ft_put_pixel(game_object, (t_coor){index.x,
                            index.y},0xFFFFFF);
            }
            index.x ++;
        }
        index.y ++;    
    }
    
}