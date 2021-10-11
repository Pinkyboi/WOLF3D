/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shooter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:56:22 by abenaiss          #+#    #+#             */
/*   Updated: 2021/10/11 15:56:24 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_game_object	*ft_clone_game_object(t_game_object *game_object)
{
	t_game_object	*game_clone;

	game_clone = malloc(sizeof(t_game_object));
	game_clone->parser = game_object->parser;
	game_clone->render_data = game_object->render_data;
	game_clone->map = game_object->map;
	game_clone->player = game_object->player;
	game_clone->ray_data = game_object->ray_data;
	game_clone->min_map = game_object->min_map;
	return (game_clone);
}

void	ft_ray_shooter(t_game_object *game_object)
{
	pthread_t		thread[NUM_THREAD];
	t_game_object	game_object_cpy[NUM_THREAD];
	int				i;

	i = -1;
	while (++i < NUM_THREAD)
	{
		game_object_cpy[i] = *ft_clone_game_object(game_object);
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