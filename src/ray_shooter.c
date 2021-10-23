/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shooter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:56:22 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/23 17:44:31 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_ray_shooter(t_game_object *game_object)
{
	pthread_t		thread[NUM_THREAD];
	t_game_object	game_object_cpy[NUM_THREAD];
	int				i;

	i = -1;
	game_object->render_data.skybox.sky.render_function(game_object,
		game_object->render_data.skybox.sky.render_data);
	while (++i < NUM_THREAD)
	{
		game_object_cpy[i] = *game_object;
		game_object_cpy[i].drawing_index.x
			= (game_object->render_data.window_resolution.x / NUM_THREAD) * i;
		game_object_cpy[i].drawing_width_end
			= (game_object->render_data.window_resolution.x / NUM_THREAD)
			* (i + 1);
		pthread_create(&thread[i], NULL, ft_ray_loop, &game_object_cpy[i]);
	}
	while (i--)
		pthread_join(thread[i], NULL);
}
