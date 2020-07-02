/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/07/02 02:05:33 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		ft_check_angle(double angle)
{
	angle = (angle < 0) ? angle + PI_2: angle;
	angle = (angle > PI_2) ? angle - PI_2: angle;
	return (angle);
}

double			ft_ray_size(t_rtv *rtv, t_d_coor ray_intersection, double angle)
{
	return((ray_intersection.x - rtv->player.position.x) * cos(angle) +
		(ray_intersection.y - rtv->player.position.y) * sin(angle));
}

double		ft_vertical_intersection(t_rtv *rtv, double angle)
{
	t_d_coor		position;
	t_d_coor		step;
	t_coor			map_coor;
	double	inverse_tan;

	inverse_tan = 1/tan(angle);
	if(angle >  M_PI)
	{ //looking up
		position.y = floor((rtv->player.position.y / BLOCK_SIZE) * BLOCK_SIZE) - 0.0000001;
		position.x = ((position.y - rtv->player.position.y) * inverse_tan) + rtv->player.position.x;
		step.y = - BLOCK_SIZE;
		step.x = step.y * inverse_tan;
	}
	if(angle < M_PI) //looking down
	{
		position.y = floor((rtv->player.position.y / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		position.x = ((position.y - rtv->player.position.y) * inverse_tan) + rtv->player.position.x;
		step.y = BLOCK_SIZE;
		step.x = step.y * inverse_tan;
	}
	if(!(angle == 0 || angle == PI_2))
	{
		int i = -1;
		while(1)
		{
			map_coor.x = (int)(position.x / BLOCK_SIZE);
			map_coor.y = (int)(position.y / BLOCK_SIZE);
			if(map_coor.x < 0 || map_coor.y < 0 || map_coor.x > rtv->proportion.x || map_coor.y > rtv->proportion.y)
				return(MAX_DIST);
			else if(rtv->map[map_coor.y][map_coor.x].type == '1')
				return(ft_ray_size(rtv, position, angle));
			else{
				position.y += step.y;
				position.x += step.x;
			}			
		}
	}
	return(MAX_DIST);
}
	
double		ft_horizontal_intersection(t_rtv *rtv,double angle)
{
	t_d_coor		position;
	t_d_coor	step;
	t_coor		map_coor;
	double		angle_tan;

	angle_tan = tan(angle);
	if(angle >  M_PI_2 && angle < M_PI_2 * 3)
	{
		position.x = floor((rtv->player.position.x / BLOCK_SIZE) * BLOCK_SIZE) - 0.0000001;
		position.y = ((position.x - rtv->player.position.x) * angle_tan) + rtv->player.position.y;
		step.x = -BLOCK_SIZE;
		step.y = step.x * angle_tan;
	}
	if(angle <  M_PI_2 || angle > M_PI_2 * 3)
	{
		position.x = floor((rtv->player.position.x / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		position.y = ((position.x - rtv->player.position.x) * angle_tan) + rtv->player.position.y;
		step.x = BLOCK_SIZE;
		step.y = step.x * angle_tan;
	}
	if(!(angle == M_PI_2 || angle == 3 * M_PI / 2))
	{
		int i = -1;
		while(1)
		{
			map_coor.x = (int)(position.x / BLOCK_SIZE);
			map_coor.y = (int)(position.y / BLOCK_SIZE);
			map_coor.y = (int)(position.y / BLOCK_SIZE);
			if(map_coor.x < 0 || map_coor.y < 0 || map_coor.x > rtv->proportion.x || map_coor.y > rtv->proportion.y)
				return(MAX_DIST);
			else if(rtv->map[map_coor.y][map_coor.x].type == '1')
				return(ft_ray_size(rtv, position, angle));
			else{
				position.y += step.y;
				position.x += step.x;
			}			
		}
	}
	return(MAX_DIST);
}

int			ft_rgb_to_int(t_color color);

void		ft_draw_line(t_rtv *rtv, t_color color)
{
	t_coor start;
	int wall_size;
	t_coor end;

	wall_size =  WIN_WIDTH * BLOCK_SIZE /  rtv->distance;
	start.x = rtv->column;
	start.y = 0;
	end = start;
	end.y  = wall_size;
	plot_line(rtv, ft_rgb_to_int(color),start, end);
}

void		ft_ray_shooter(t_rtv *rtv)
{
	t_coor first_ray;
	double	step;
	double	first_angle;
	double		distence[2];
	int wall_size;
	t_coor start;
	t_coor end;

	step = FOV / WIN_WIDTH;
	first_angle = rtv->player.view_angle - (FOV / 2);
	rtv->column = 500-1;
	while(++rtv->column < WIN_WIDTH * 2)
	{
		rtv->distance = 0;
		first_angle = ft_check_angle(first_angle);
		distence[0] = ft_horizontal_intersection(rtv,first_angle);
		distence[1] = ft_vertical_intersection(rtv,first_angle);
		if(distence[0] < distence[1])
			rtv->color = (t_color){.8, 0, 0};
		else
			rtv->color = (t_color){1, 0, 0};
		rtv->distance  =  ((distence[0] < distence[1]) ? distence[0] : distence[1]) * cos(rtv->player.view_angle - first_angle);
		wall_size = (int)(WIN_WIDTH * BLOCK_SIZE / rtv->distance);
		start = (t_coor){rtv->column, (WIN_WIDTH / 2) - wall_size/2};
		end = (t_coor){rtv->column, (WIN_WIDTH / 2) + wall_size/2};
		plot_line(rtv, ft_rgb_to_int(rtv->color),start, end);
		first_angle += step;
	}
}
