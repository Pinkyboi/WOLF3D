/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_strock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/07/22 20:21:54 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_print_coordinate(t_coor position)
{
	printf("(%d, %d)\n", position.x, position.y);
}

int 		ft_check_walls(t_rtv *rtv, int key)
{
	t_coor position;

	if(key == UP)
		position = (t_coor){(rtv->player.position.x + rtv->player.dx) / BLOCK_SIZE,
			(rtv->player.position.y + rtv->player.dy) / BLOCK_SIZE};
	if(key == DOWN)
		position = (t_coor){(rtv->player.position.x - rtv->player.dx) / BLOCK_SIZE,
			(rtv->player.position.y - rtv->player.dy) / BLOCK_SIZE};
	if(position.x <= 0 || position.x >= rtv->map_dimentions.x)
		return (0);
	if(position.y <= 0 || position.y >= rtv->map_dimentions.y)
		return (0);
	if(rtv->map[position.y][position.x].type != '0' && rtv->map[position.y][position.x].type != 'P' )
		return (0);
	if(rtv->map[position.y][position.x].type == '0')
	{
		rtv->map[rtv->player.position.y / BLOCK_SIZE][rtv->player.position.x / BLOCK_SIZE].type = '0';
		rtv->map[position.y][position.x].type = 'P';
	}
	return (1);
}

void 		ft_movement(int key, t_rtv *rtv)
{
	if(key == RIGHT || key == LEFT)
	{
		if(key == LEFT)
			rtv->player.view_angle -= .1;
		if(key == RIGHT)
			rtv->player.view_angle += .1;
		rtv->player.view_angle = ft_check_angle(rtv->player.view_angle);
		rtv->player.dx = rtv->player.step * cos(rtv->player.view_angle);
		rtv->player.dy = rtv->player.step * sin(rtv->player.view_angle);
	}
	if(key == UP)
	{
		if(ft_check_walls(rtv, UP))
		{
			rtv->player.position.x += (int)rtv->player.dx;
			rtv->player.position.y += (int)rtv->player.dy;
		}
	}
	if(key == DOWN)
	{
		if(ft_check_walls(rtv, DOWN))
		{
			rtv->player.position.x -= (int)rtv->player.dx;
			rtv->player.position.y -= (int)rtv->player.dy;
		}
	}	
}

int			ft_key_stroke(int key, t_rtv *rtv)
{
	(key == EXIT) ? ft_exit(rtv) : 1;
	ft_clear_mlx(&rtv->mlx, rtv);
	if(key == RIGHT || key == LEFT || key== UP || key == DOWN)
		ft_movement(key, rtv);
	ft_ray_shooter(rtv);
	ft_draw_map(rtv, 10);
	// ft_minimap(rtv);
	// ft_draw_block(rtv, (t_coor){(int)(rtv->player.position.x * 10 / BLOCK_SIZE),
	// 	(int)(rtv->player.position.y * 10 / BLOCK_SIZE)}, 10, 0xFF0000);
	mlx_put_image_to_window(rtv->mlx.mlx_ptr,
		rtv->mlx.win, rtv->mlx.img.img_ptr, 0, 0);
	return (0);
}