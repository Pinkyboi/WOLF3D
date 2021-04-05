/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:15:21 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/05 13:15:22 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf3d.h"

void    ft_setup_dda(t_wolf *wolf, t_d_coor *rayStep, t_d_coor *rayDistance, t_coor *gridStep)
{
	t_d_coor ray;

	ray = wolf->player.current_ray;
	ray = ft_normalise_vector2D(ray);
	*rayStep = (t_d_coor){(!ray.x) ? 0 :
		sqrtf(1 + FT_SQR(ray.y / ray.x)), (!ray.y) ? 0 :
		sqrtf(1 + FT_SQR(ray.x / ray.y))};
	if(ray.x < 0)
	{
		gridStep->x = -1;
		rayDistance->x = (wolf->player.position.x  - (float)wolf->player.grid_position.x) * rayStep->x;
	}
	else
	{
		gridStep->x = 1;
		rayDistance->x = ((float)(wolf->player.grid_position.x + 1.0) - wolf->player.position.x) * rayStep->x;
	}
	if(ray.y < 0)
	{
		gridStep->y = -1;
		rayDistance->y = (wolf->player.position.y  - (float)wolf->player.grid_position.y) * rayStep->y;
	}
	else
	{
		gridStep->y = 1;
		rayDistance->y = ((float)(wolf->player.grid_position.y + 1.0) - wolf->player.position.y) * rayStep->y;
	}
}

void	ft_define_check_step(t_wolf *wolf, t_d_coor ray){
	t_coor		playerGridPos;
	t_coor		gridStep;
	t_d_coor	rayStep;
	t_d_coor	rayDistance;

	playerGridPos = (t_coor){wolf->player.position.x, wolf->player.position.y};
	ft_setup_dda(wolf, &rayStep, &rayDistance, &gridStep);
	while(wolf->player.hit_infos.distance < MAX_DIST){
		if(rayDistance.x < rayDistance.y){
			playerGridPos.x += gridStep.x;
			wolf->player.hit_infos.distance = rayDistance.x;
			wolf->player.hit_infos.wall_type = 'V';
			rayDistance.x += rayStep.x;
		}
		else
		{
			playerGridPos.y += gridStep.y;
			wolf->player.hit_infos.distance = rayDistance.y;
			wolf->player.hit_infos.wall_type = 'H';
			rayDistance.y += rayStep.y;
		}
		if(playerGridPos.x >= 0 && playerGridPos.x <= wolf->map_dimentions.x &&
			playerGridPos.y >= 0 && playerGridPos.y <= wolf->map_dimentions.y)
			if(wolf->map[playerGridPos.y][playerGridPos.x].type == '1')
				break;
	}
}
t_hit_infos	ft_define_check_step_1(t_wolf *wolf, t_d_coor ray, t_d_coor playerWorldPos){
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
		if(playerGridPos.x >= 0 && playerGridPos.x <= wolf->map_dimentions.x &&
			playerGridPos.y >= 0 && playerGridPos.y <= wolf->map_dimentions.y)
			if(wolf->map[playerGridPos.y][playerGridPos.x].type == '1')
				break;
	}
	return(hitInfos);
}