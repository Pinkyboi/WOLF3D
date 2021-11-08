/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:32:17 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/08 19:03:29 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static unsigned long	g_old_time;
static unsigned long	g_time;

static void	ft_framerate_limitor(t_game_object *game_object)
{
	double	frame_time;

	g_old_time = g_time;
	g_time = clock();
	frame_time = (double)(g_time - g_old_time) / (double)CLOCKS_PER_SEC;
	game_object->player.step = frame_time * 3.0;
	game_object->player.tilt_step = ft_clip_max_d(0.05, frame_time * 0.4);
	game_object->player.rot_step = ft_clip_max_d(0.08, frame_time * 0.4);
}

int	ft_frame_loop(void *arg)
{
	t_game_object	*game_object;

	game_object = arg;
	if (ft_any_key_pressed() == 1)
	{
		ft_clear_mlx(game_object);
		ft_framerate_limitor(game_object);
		ft_run(game_object);
		ft_movement(game_object);
		ft_head_tilt(game_object);
		ft_ray_shooter(game_object);
		ft_print_mini_map(game_object, game_object->min_map.center_position);
		mlx_put_image_to_window(game_object->render_data.mlx.mlx_ptr,
			game_object->render_data.mlx.mlx_win,
			game_object->render_data.mlx.mlx_img.img_ptr, 0, 0);
	}
	return (0);
}
