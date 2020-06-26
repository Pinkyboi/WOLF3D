/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/06/26 01:40:25 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		ft_check_angle(double angle)
{
	angle = (angle < 0) ? angle + PI_2: angle;
	angle = (angle > PI_2) ? angle - PI_2: angle;
	return (angle);
}

double			ft_ray_size(t_rtv *rtv, t_coor ray_intersection, double angle)
{
	double x = fabs((rtv->player.position.x - ray_intersection.x) / cos(angle));
	double y = fabs((rtv->player.position.y - ray_intersection.y) / sin(angle));
	return((x > y) ? y : x);
}

t_coor		ft_horizontal_intersection(t_rtv *rtv,double angle)
{
	t_coor	position;
	double	xstep;
	double	ystep;
	double	inverse_tan;
	double	angle_tan;
	
	inverse_tan = 1/tan(angle);
	if(angle >  M_PI){ //looking up
		position.y = (int)(rtv->player.position.y / BLOCK_SIZE) * BLOCK_SIZE - 0.000001;
		position.x = ((position.y - rtv->player.position.y) * inverse_tan) + rtv->player.position.x;
		ystep = -BLOCK_SIZE;
		xstep = ystep * inverse_tan;
	}
	if(angle < M_PI) //looking down
	{
		position.y = (int)((rtv->player.position.y / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		position.x = ((position.y - rtv->player.position.y) * inverse_tan) + rtv->player.position.x;
		ystep = BLOCK_SIZE;
		xstep = ystep * inverse_tan;
	}
	double distV = 100000;
	t_coor positionV;
	if(angle == 0 || angle == PI_2)
		positionV = rtv->player.position;
	else
	{
		int i = -1;
		while(++i < 8)
		{
			int x = (int)(position.x / BLOCK_SIZE);
			int y = (int)(position.y / BLOCK_SIZE);
			if(x < 0 || y < 0 || x > 8 || y > 8 || map[y][x]){
				positionV = position;
				distV = ft_ray_size(rtv, position, angle);
				break;
			}
			else
			{
				position.y += ystep;
				position.x += xstep;			
			}
		}	
	}
	angle_tan = tan(angle);
	if(angle >  M_PI_2 && angle < M_PI_2 * 3)
	{ //looking left
		position.x = (int)(rtv->player.position.x / BLOCK_SIZE) * BLOCK_SIZE - 1;
		position.y = ((position.x - rtv->player.position.x) * angle_tan) + rtv->player.position.y;
		xstep = -BLOCK_SIZE;
		ystep = xstep * angle_tan;
	}
	if(angle <  M_PI_2 || angle > M_PI_2 * 3)
	{ //looking right
		position.x = (int)((rtv->player.position.x / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		position.y = ((position.x - rtv->player.position.x) * angle_tan) + rtv->player.position.y;
		xstep = BLOCK_SIZE;
		ystep = xstep * angle_tan;
	}
	double distH = 100000;
	t_coor positionH;
	if(angle == M_PI_2 || angle == 3 * M_PI / 2)
		positionH = rtv->player.position;
	else
	{
		int i = -1;
		while(++i < 8)
		{
			int x = (int)(position.x / BLOCK_SIZE);
			int y = (int)(position.y / BLOCK_SIZE);
			if(x < 0 || y < 0 || x > 8 || y > 8 || map[y][x]){
				positionH = position;
				distH = ft_ray_size(rtv, position, angle);
				break;
			}
			else{
				position.y += ystep;
				position.x += xstep;
			}			
		}
	}
	return((distH <= distV) ? positionH : positionV);
}

void		ft_ray_shooter(t_rtv *rtv)
{
	t_coor first_ray;
	double	step;
	double	first_angle;

	step = FOV / RAY_NUMBER;
	first_angle = rtv->player.view_angle - (FOV / 2);
	int i = -1;
	while(++i < RAY_NUMBER)
	{
		first_angle = ft_check_angle(first_angle);
		plot_line(rtv, 0xFF00FF, rtv->player.position, ft_horizontal_intersection(rtv,first_angle));
		first_angle += step;
	}
}
