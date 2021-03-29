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

void		ft_print_d_coordinate(t_d_coor position)
{
	printf("(%f, %f)\n", position.x, position.y);
}

int 		ft_check_walls(t_rtv *rtv, int key)
{
	t_coor position;
	t_coor back_position;

		back_position = (t_coor){rtv->player.position.x, rtv->player.position.y};
	if(key == UP)
		position = (t_coor){rtv->player.position.x + rtv->player.dx,
			rtv->player.position.y + rtv->player.dy};
	if(key == DOWN)
		position = (t_coor){(rtv->player.position.x - rtv->player.dx),
			(rtv->player.position.y - rtv->player.dy)};
	if(position.x <= 0 || position.x >= rtv->map_dimentions.x)
		return (0);
	if(position.y <= 0 || position.y >= rtv->map_dimentions.y)
		return (0);
	if(rtv->map[position.y][position.x].type != '0' && rtv->map[position.y][position.x].type != 'P' )
		return (0);
	if(rtv->map[position.y][position.x].type == '0')
	{
		rtv->map[back_position.y][back_position.x].type = '0';
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
		rtv->player.dx = 1.0 * cos(rtv->player.view_angle);
		rtv->player.dy = 1.0 * sin(rtv->player.view_angle);
	}
	if(key == UP)
	{
		if(ft_check_walls(rtv, UP))
		{
			rtv->player.position.x += rtv->player.dx;
			rtv->player.position.y += rtv->player.dy;
		}
	}
	if(key == DOWN)
	{
		if(ft_check_walls(rtv, DOWN))
		{
			rtv->player.position.x -= rtv->player.dx;
			rtv->player.position.y -= rtv->player.dy;
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
	ft_minimap(rtv);
	mlx_put_image_to_window(rtv->mlx.mlx_ptr,
		rtv->mlx.win, rtv->mlx.img.img_ptr, 0, 0);
	return (0);
}