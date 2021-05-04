/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:30:21 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/04 14:30:29 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void 		ft_movement(int key, t_game_object *game_object)
{
	if(key == RIGHT || key == LEFT)
	{
		if(key == LEFT)
			game_object->player.orientation -= .1;
		if(key == RIGHT)
			game_object->player.orientation += .1;
		game_object->player.orientation = ft_check_angle(game_object->player.orientation);
		game_object->player.movement = ft_scale_vector2D(
		ft_angleToVector2D(game_object->player.orientation),
			game_object->player.step);
	}
	if(key == FOREWORD)
	{
		game_object->player.world_position = ft_add_vector2D(game_object->player.world_position,
									game_object->player.movement);
		game_object->player.grid_position =(t_coor){game_object->player.world_position.x,
										game_object->player.world_position.y};
	}
	if(key == BACKWARD)
	{
		game_object->player.world_position = ft_sub_vector2D(game_object->player.world_position,
									game_object->player.movement);
		game_object->player.grid_position =(t_coor){game_object->player.world_position.x,
										game_object->player.world_position.y};
	}	
}

int			ft_exit(t_game_object *game_object)
{
	(void)game_object;
	exit(0);
}

void		ft_clear_mlx(t_mlx *mlx, t_coor resolution)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->mlx_img.img_ptr);
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx->mlx_img.img_ptr =
		mlx_new_image(mlx->mlx_ptr, resolution.x, resolution.y);
	mlx->mlx_img.img_data =
	(int*)mlx_get_data_addr(mlx->mlx_img.img_ptr, &mlx->mlx_img.bpp,
			&mlx->mlx_img.size_l, &mlx->mlx_img.endian);
}

int			ft_key_stroke(int key, t_game_object *game_object)
{
	(key == EXIT) ? ft_exit(game_object) : 1;
	
	if(key == RIGHT || key == LEFT || key== FOREWORD || key == BACKWARD){
		ft_clear_mlx(&game_object->render_data.mlx, game_object->render_data.window_resolution);
		ft_movement(key, game_object);
		ft_ray_shooter(game_object);
		mlx_put_image_to_window(game_object->render_data.mlx.mlx_ptr,
				game_object->render_data.mlx.mlx_win, game_object->render_data.mlx.mlx_img.img_ptr, 0, 0);
	}
	return(0);
}