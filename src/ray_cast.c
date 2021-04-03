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

double		ft_check_angle(double angle)
{
	angle = (angle < 0) ? angle + PI_2: angle;
	angle = (angle > PI_2) ? angle - PI_2: angle;
	return (angle);
}

t_d_coor		angleToVector2D(double alpha){
	return((t_d_coor){cos(alpha), sin(alpha)});
}
double			ft_ray_size(t_rtv *rtv, t_d_coor ray_intersection, double angle)
{
	return((ray_intersection.x - rtv->player.position.x) * cos(angle) +
		(ray_intersection.y - rtv->player.position.y) * sin(angle));
}
t_d_coor		ft_add_vector2D(t_d_coor vector2D, t_d_coor second_vector2D){
	vector2D.x += second_vector2D.x;
	vector2D.y += second_vector2D.y;

	return(vector2D);
}

t_d_coor		ft_scale_vector2D(t_d_coor vector2D, double scale){
	vector2D.x *= scale;
	vector2D.y *= scale;
	return(vector2D);
}

t_d_coor	ft_normalise_vector2D(t_d_coor vector){
	double norm = sqrtf(FT_SQR(vector.x) + FT_SQR(vector.y));
	vector.x /= norm;
	vector.y /= norm;
	
	return(vector);
}

t_hit_infos	ft_define_check_step(t_rtv *rtv, t_d_coor ray, t_d_coor playerWorldPos){
	t_coor		playerGridPos;
	t_coor		gridStep;
	t_d_coor	rayStep;
	t_d_coor	rayDistance;
	t_hit_infos	hitInfos;

	playerGridPos = (t_coor){playerWorldPos.x, playerWorldPos.y};
	ray = ft_normalise_vector2D(ray);
	rayStep = (t_d_coor){(ray.x == 0.0) ? 0 : sqrtf(1 + FT_SQR(ray.y / ray.x)), (ray.y == 0.0) ? 0 : sqrtf(1 + FT_SQR(ray.x / ray.y))};
	if(ray.x < 0)
	{
		gridStep.x = -1;
		rayDistance.x = (playerWorldPos.x  - (float)playerGridPos.x) * rayStep.x;
	}
	else
	{
		gridStep.x = 1;
		rayDistance.x = ((float)(playerGridPos.x + 1.0) - playerWorldPos.x) * rayStep.x;
	}
	if(ray.y < 0)
	{
		gridStep.y = -1;
		rayDistance.y = (playerWorldPos.y  - (float)playerGridPos.y) * rayStep.y;
	}
	else
	{
		gridStep.y = 1;
		rayDistance.y = ((float)(playerGridPos.y + 1.0) - playerWorldPos.y) * rayStep.y;
	}
	while(hitInfos.distance < MAX_DIST){
		if(rayDistance.x < rayDistance.y){
			playerGridPos.x += gridStep.x;
			hitInfos.distance = rayDistance.x;
			hitInfos.wall_type = 'V';
			rayDistance.x += rayStep.x;
		}
		else
		{
			playerGridPos.y += gridStep.y;
			hitInfos.distance = rayDistance.y;
			hitInfos.wall_type = 'H';
			rayDistance.y += rayStep.y;
		}
		if(playerGridPos.x >= 0 && playerGridPos.x <= rtv->map_dimentions.x &&
			playerGridPos.y >= 0 && playerGridPos.y <= rtv->map_dimentions.y)
			if(rtv->map[playerGridPos.y][playerGridPos.x].type == '1')
				break;
	}
	return(hitInfos);
}

void line(t_rtv *rtv, t_coor pt0,t_coor pt1) {
 
  int dx = abs(pt1.x-pt0.x), sx = pt0.x<pt1.x ? 1 : -1;
  int dy = abs(pt1.y-pt0.y), sy = pt0.y<pt1.y ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    ft_put_pixel(rtv,pt0,0xFF0000);
    if (pt0.x==pt1.x && pt0.y==pt1.y) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; pt0.x += sx; }
    if (e2 < dy) { err += dx; pt0.y += sy; }
  }
}

int			ft_get_textureX_coor(t_rtv *rtv)
{
	double wall_index;

	t_d_coor end = ft_add_vector2D(rtv->player.position,
		ft_scale_vector2D(rtv->player.current_ray, rtv->player.hit_infos.distance));
	wall_index = (rtv->player.hit_infos.wall_type == 'V') ? end.y : end.x;
	wall_index -= (int)wall_index;
	int texture_index = wall_index * (double)rtv->texture_dimention.y;
	return(texture_index);
}

void		ft_minimap(t_rtv *rtv);

void		ft_ray_shooter(t_rtv *rtv)
{
	t_coor first_ray;
	double	step;
	double	first_angle;
	double	distence[2];
	t_hit_infos infos;
	int wall_size;
	int start;
	int end;

	step = FOV / WIN_WIDTH;
	first_angle = rtv->player.view_angle - (FOV / 2);
	rtv->column = -1;
	double stp1 = (double)rtv->texture_dimention.x / (double)BLOCK_SIZE;
	start = 0;
	while(++rtv->column < WIN_WIDTH)
	{
		infos.distance = 0;
		first_angle = ft_check_angle(first_angle);
		rtv->player.current_ray = angleToVector2D(first_angle);
		rtv->player.hit_infos = ft_define_check_step(rtv, rtv->player.current_ray, rtv->player.position);
		rtv->distance = rtv->player.hit_infos.distance * (double)BLOCK_SIZE * cos(rtv->player.view_angle - first_angle);
		double j  = ft_get_textureX_coor(rtv);

		wall_size = (int)(WIN_WIDTH * BLOCK_SIZE / rtv->distance);
		start = ((WIN_HEIGHT / 2) - wall_size/2) - 1;
		end  = (WIN_HEIGHT / 2) + wall_size/2;
		double stp = (double)rtv->texture_dimention.y / wall_size;
		double i = 0;
		int color;
		int k = -1;
		while(++k <= start)
		{
			double wall_ratio = abs(k - (WIN_HEIGHT / 2));
			double distance = 32.0 / wall_ratio * WIN_WIDTH /cos(rtv->player.view_angle - first_angle) / 64.0;
			t_d_coor texture_ratio;

			texture_ratio.y = rtv->player.position.y + (distance * sin(first_angle));
			texture_ratio.x = rtv->player.position.x + (distance * cos(first_angle));
			texture_ratio.x -= (int)texture_ratio.x;
			texture_ratio.y -= (int)texture_ratio.y;
			texture_ratio.x *= rtv->texture_dimention.x;
			texture_ratio.y *= rtv->texture_dimention.y;
			color = ft_scale_color_int(rtv->texture[(int)((int)texture_ratio.y * rtv->texture_dimention.x + (int)texture_ratio.x)], 0.6);
			ft_put_pixel(rtv,(t_coor){rtv->column ,k}, color);
		}
		while(++start < end)
		{
			if(rtv->player.hit_infos.wall_type == 'H')
				color = ft_scale_color_int(rtv->texture[(int)((int)i * rtv->texture_dimention.x + (int)(j * stp1))], 1);
			else
				color = ft_scale_color_int(rtv->texture[(int)((int)i * rtv->texture_dimention.x + (int)(j * stp1))], .7);
			ft_put_pixel(rtv,(t_coor){rtv->column ,start}, color);
			i += stp;
		}
		start--;
		while(++start < WIN_HEIGHT)
		{
			double wall_ratio = abs(start - (WIN_HEIGHT / 2));
			double distance = 32.0 / wall_ratio * WIN_WIDTH /cos(rtv->player.view_angle - first_angle) / 64.0;
			t_d_coor texture_ratio;

			texture_ratio.y = rtv->player.position.y + (distance * sin(first_angle));
			texture_ratio.x = rtv->player.position.x + (distance * cos(first_angle));
			texture_ratio.x -= (int)texture_ratio.x;
			texture_ratio.y -= (int)texture_ratio.y;
			texture_ratio.x *= rtv->texture_dimention.x;
			texture_ratio.y *= rtv->texture_dimention.y;
			color = ft_scale_color_int(rtv->texture[(int)((int)texture_ratio.y * rtv->texture_dimention.x + (int)texture_ratio.x)], 0.6);
			ft_put_pixel(rtv,(t_coor){rtv->column ,start}, color);
		}
		first_angle += step;
	}
}
