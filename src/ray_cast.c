/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/07/22 20:17:48 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_ray_shooter(t_wolf *wolf)
{
	double	step;
	double	first_angle;
	int 	wall_size;
	int 	start;
	int 	end;
	int color;
	double i;
	double j;

	step = FOV / WIN_WIDTH;
	first_angle = wolf->player.view_angle - (FOV / 2);
	wolf->column = -1;
	double stp1 = (double)wolf->texture_dimention.x / (double)BLOCK_SIZE;
	start = 0;
	while(++wolf->column < WIN_WIDTH)
	{
		wolf->player.hit_infos.distance = 0;
		first_angle = ft_check_angle(first_angle);
		wolf->player.current_ray = ft_angleToVector2D(first_angle);
		ft_define_check_step(wolf, wolf->player.current_ray);

		wolf->distance = wolf->player.hit_infos.distance * (double)BLOCK_SIZE * cos(wolf->player.view_angle - first_angle);
		j  = ft_get_textureX_coor(wolf);
		wall_size = (int)(WIN_WIDTH * BLOCK_SIZE / wolf->distance);
		start = ((WIN_HEIGHT / 2) - wall_size/2) - 1 ;
		end  = start + wall_size;
		double stp = (double)wolf->texture_dimention.y / wall_size;
		
		i = 0;
		ft_ceiling_or_floor(wolf, first_angle, (t_coor){0, start + 1});
		while(++start < end)
		{
			if(wolf->player.hit_infos.wall_type == 'H')
				color = ft_scale_color_int(wolf->texture[(int)((int)i * wolf->texture_dimention.x + (int)(j * stp1))], 1);
			else
				color = ft_scale_color_int(wolf->texture[(int)((int)i * wolf->texture_dimention.x + (int)(j * stp1))], .7);
			ft_put_pixel(wolf,(t_coor){wolf->column ,start}, color);
			i += stp;
		}
		ft_ceiling_or_floor(wolf, first_angle, (t_coor){start, WIN_HEIGHT});
		first_angle += step;
	}
}


void ft_ceiling_or_floor(t_wolf *wolf, double first_angle, t_coor range)
{
	double wall_ratio;
	double distance;
	double color;
	t_d_coor texture_ratio;

	while(range.x < range.y)
	{
		wall_ratio = abs(range.x - (WIN_HEIGHT / 2));
		distance = 32.0 / wall_ratio * WIN_WIDTH /cos(wolf->player.view_angle - first_angle) / 64.0;
		texture_ratio.y = wolf->player.position.y + (distance * sin(first_angle));
		texture_ratio.x = wolf->player.position.x + (distance * cos(first_angle));
		texture_ratio.x -= (int)texture_ratio.x;
		texture_ratio.y -= (int)texture_ratio.y;
		texture_ratio.x *= wolf->texture_dimention.x;
		texture_ratio.y *= wolf->texture_dimention.y;
		color = ft_scale_color_int(wolf->texture[(int)((int)texture_ratio.y * wolf->texture_dimention.x + (int)texture_ratio.x)], 0.6);
			ft_put_pixel(wolf,(t_coor){wolf->column ,range.x}, color);
		range.x++;
	}
}
