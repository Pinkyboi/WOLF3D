/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 19:47:54 by abenaiss          #+#    #+#             */
/*   Updated: 2020/07/21 22:28:42 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_draw_block(t_wolf *wolf,t_d_coor position, int size, int color)
{
	int i = -1;
	while(++i < size)
	{
		int j = -1;
		while(++j < size)
			ft_put_pixel(wolf, (t_coor){position.x + j, position.y + i},color);
	}
}

void		ft_draw_map(t_wolf *wolf, int block_size)
{
	int i = -1;
	wolf->column = 0;
	while(++i <= wolf->map_dimentions.y)
	{
		int j = -1;
		wolf->row = 0;
		while(++j <= wolf->map_dimentions.x){
			if(wolf->map[i][j].type == '1')
				ft_draw_block(wolf,(t_d_coor){wolf->row, wolf->column}, block_size, 0xFFFFFF);
			else if(wolf->map[i][j].type == 'P')
				ft_draw_block(wolf,(t_d_coor){wolf->row, wolf->column}, block_size, 0xFF0000);
			wolf->row += block_size;
		}
		wolf->column += block_size;
	}
}

void		ft_minimap(t_wolf *wolf)
{
	ft_draw_map(wolf, 10);
}
