/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_strock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/06/30 19:33:32 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void 		ft_movement(int key, t_rtv *rtv)
{
	if(key == RIGHT || key == LEFT)
	{
		if(key == RIGHT)
			rtv->player.view_angle -= .1;
		if(key == LEFT)
			rtv->player.view_angle += .1;
		rtv->player.view_angle = ft_check_angle(rtv->player.view_angle);
		rtv->player.dx = rtv->player.step * cos(rtv->player.view_angle);
		rtv->player.dy = rtv->player.step * sin(rtv->player.view_angle);
	}
	if(key == UP)
	{
		rtv->player.position.x += rtv->player.dx;
		rtv->player.position.y += rtv->player.dy;
	}
	if(key == DOWN)
	{
		rtv->player.position.x -= rtv->player.dx;
		rtv->player.position.y -= rtv->player.dy;
	}	
}

int			ft_key_stroke(int key, t_rtv *rtv)
{
	(key == EXIT) ? ft_exit(rtv) : 1;
	ft_clear_mlx(&rtv->mlx, rtv);
	if(key == RIGHT || key == LEFT || key== UP || key == DOWN)
		ft_movement(key, rtv);
	ft_draw_map(rtv);
	ft_ray_shooter(rtv);
	ft_draw_block(rtv, (t_coor){rtv->player.position.x - 5, rtv->player.position.y - 5}, 10, 0xFF0000);
	mlx_put_image_to_window(rtv->mlx.mlx_ptr,
		rtv->mlx.win, rtv->mlx.img.img_ptr, 0, 0);
	return (0);
}