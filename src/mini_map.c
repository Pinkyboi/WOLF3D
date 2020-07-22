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

void		ft_draw_block(t_rtv *rtv,t_coor position, int size, int color)
{
	int i = -1;
	while(++i < size)
	{
		int j = -1;
		while(++j < size)
			ft_put_pixel(rtv, (t_coor){position.x + j, position.y + i},color);
	}
}

void		ft_draw_map(t_rtv *rtv, int block_size)
{
	int i = -1;
	rtv->column = 0;
	while(++i <= rtv->map_dimentions.y)
	{
		int j = -1;
		rtv->row = 0;
		while(++j <= rtv->map_dimentions.x){
			if(rtv->map[i][j].type == '1')
				ft_draw_block(rtv,(t_coor){rtv->row, rtv->column}, block_size, 0xFFFFFF);
			if(rtv->map[i][j].type == 'P')
				ft_draw_block(rtv,(t_coor){rtv->row, rtv->column}, block_size, 0xFF0000);
			rtv->row += block_size;
		}
		rtv->column += block_size;
	}
}

// void		ft_print_coordinate(t_coor position)
// {
// 	printf("(%d, %d)\n", position.x, position.y);
// }

void		ft_minimap(t_rtv *rtv)
{
	// t_coor position;
	// ft_draw_map(rtv, BLOCK_SIZE);
	// position = (t_coor){rtv->player.position.x / BLOCK_SIZE, rtv->player.position.y / BLOCK_SIZE};
	
	// ft_draw_block(rtv, (t_coor){position.x, position.y}, 2, 0xFF0000);
}
