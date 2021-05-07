/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:30:21 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/06 23:57:45 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_put_pixel(t_game_object *game_object, t_coor position, int color)
{
	t_coor resolution;

	resolution = game_object->render_data.window_resolution;
	if (position.x >= 0 && position.x < resolution.x &&
		position.y >= 0 && position.y < resolution.y)
		game_object->render_data.mlx.mlx_img.img_data[
			(int)(position.y * resolution.x + position.x)] = color;
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