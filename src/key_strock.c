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

int 		ft_check_walls(t_wolf *wolf, int key)
{
	t_coor position;
	t_coor back_position;

	back_position = (t_coor){wolf->player.position.x, wolf->player.position.y};
	if(key == UP)
		position = (t_coor){wolf->player.position.x + wolf->player.movement.x,
			wolf->player.position.y + wolf->player.movement.y};
	if(key == DOWN)
		position = (t_coor){(wolf->player.position.x - wolf->player.movement.x),
			(wolf->player.position.y - wolf->player.movement.y)};
	if(position.x <= 0 || position.x >= wolf->map_dimentions.x)
		return (0);
	if(position.y <= 0 || position.y >= wolf->map_dimentions.y)
		return (0);
	if(wolf->map[position.y][position.x].type != '0' &&
		wolf->map[position.y][position.x].type != 'P' )
		return (0);
	if(wolf->map[position.y][position.x].type != '1')
	{
		wolf->map[back_position.y][back_position.x].type = wolf->player.current_tile;
		wolf->player.current_tile = wolf->map[position.y][position.x].type;
		wolf->map[position.y][position.x].type = 'P';
	}
	return (1);
}

void 		ft_movement(int key, t_wolf *wolf)
{
	if(key == RIGHT || key == LEFT)
	{
		if(key == LEFT)
			wolf->player.view_angle -= .1;
		if(key == RIGHT)
			wolf->player.view_angle += .1;
		wolf->player.view_angle = ft_check_angle(wolf->player.view_angle);
	wolf->player.movement = ft_scale_vector2D(
		ft_angleToVector2D(wolf->player.view_angle),
			wolf->player.step);
	}
	if(key == UP)
	{
		if(ft_check_walls(wolf, UP))
		{
			wolf->player.position = ft_add_vector2D(wolf->player.position,
									wolf->player.movement);
			wolf->player.grid_position =(t_coor){wolf->player.position.x,
										wolf->player.position.y};
		}
	}
	if(key == DOWN)
	{
		if(ft_check_walls(wolf, DOWN))
		{
			wolf->player.position = ft_sub_vector2D(wolf->player.position,
									wolf->player.movement);
			wolf->player.grid_position =(t_coor){wolf->player.position.x,
										wolf->player.position.y};
		}
	}	
}

int			ft_key_hold(int key, t_wolf *wolf){
	 
	 if(key == 257){
		wolf->player.step -= 0.6;
		wolf->player.movement = ft_scale_vector2D(
		ft_angleToVector2D(wolf->player.view_angle),
			wolf->player.step);
		wolf->player.is_running = 0;
	 }
	 	
	return(0);
}
void		ft_jump(int key, t_wolf *wolf){

}
int			ft_key_stroke(int key, t_wolf *wolf)
{
	(key == EXIT) ? ft_exit(wolf) : 1;
	ft_clear_mlx(&wolf->mlx, wolf);
	if(key == 257 && !wolf->player.is_running){
		wolf->player.step += .6;
		wolf->player.movement = ft_scale_vector2D(
		ft_angleToVector2D(wolf->player.view_angle),
			wolf->player.step);
		wolf->player.is_running = 1;
	}
	if(key == RIGHT || key == LEFT || key== UP || key == DOWN)
		ft_movement(key, wolf);

	ft_ray_shooter(wolf);
	ft_minimap(wolf);
	mlx_put_image_to_window(wolf->mlx.mlx_ptr,
		wolf->mlx.win, wolf->mlx.img.img_ptr, 0, 0);
	return (0);
}

