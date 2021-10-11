/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/17 12:12:45 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void	ft_wireframe_render(t_game_object *game_object)
{
	t_block_list	*current_block;

	current_block = game_object->current_block;
	if (game_object->current_block)
		ft_wireframe_draw(game_object);
}

void	ft_textured_render(t_game_object *game_object)
{
	t_render		render_data;
	t_block_list	*current_block;

	current_block = game_object->current_block;
	if (game_object->current_block)
	{
		render_data = game_object->current_block->render.render_data;
		current_block->render.render_function(game_object, render_data);
	}
}

void	ft_get_wall_distance(t_game_object *game_object, double first_angle)
{
	ft_define_check_step(game_object);
	game_object->ray_data.straight_distance
		= game_object->ray_data.hit_distance;
	game_object->ray_data.straight_distance *= (double)BLOCK_SIZE;
	game_object->ray_data.straight_distance
		*= cos(game_object->player.orientation - first_angle);
	game_object->ray_data.angle = first_angle;
}

void	*ft_ray_loop(void *arg)
{
	double		step;
	double		first_angle;
	t_game_object	*game_object;

	game_object = arg;
	step = PLAYER_FOV / game_object->render_data.window_resolution.x;
	first_angle = game_object->player.orientation - (PLAYER_FOV / 2);
	first_angle += game_object->drawing_index.x * step;
	first_angle = ft_check_angle(first_angle);
	game_object->render_data.skybox.sky.render_function(game_object,
		game_object->render_data.skybox.sky.render_data);
	while (game_object->drawing_index.x
		<= game_object->drawing_width_end)
	{
		game_object->ray_data.hit_distance = 0;
		game_object->current_block = NULL;
		first_angle = ft_check_angle(first_angle);
		game_object->ray_data.current_ray = ft_angleToVector2D(first_angle);
		ft_get_wall_distance(game_object, first_angle);
		game_object->render_data.render_function(game_object);
		first_angle += step;
		game_object->drawing_index.x++;
	}
	return(NULL);
}

t_game_object*			ft_clone_game_object(t_game_object *game_object)
{
	t_game_object	*game_clone;

	game_clone = malloc(sizeof(t_game_object));
	game_clone->parser =  game_object->parser;
	game_clone->render_data = game_object->render_data;
	game_clone->map = game_object->map;
	game_clone->player = game_object->player;
	game_clone->ray_data = game_object->ray_data;
	game_clone->min_map = game_object->min_map;
	return game_clone;
}

void					ft_ray_shooter(t_game_object *game_object)
{
	pthread_t	thread[NUM_THREAD];
	t_game_object		game_object_cpy[NUM_THREAD];
	int			i;

	i = -1;
	while (++i < NUM_THREAD)
	{
		game_object_cpy[i] = *ft_clone_game_object(game_object);
		game_object_cpy[i].drawing_index.x = (game_object->render_data.window_resolution.x / NUM_THREAD) * i;
		game_object_cpy[i].drawing_width_end = (game_object->render_data.window_resolution.x / NUM_THREAD) * (i + 1);
		pthread_create(&thread[i], NULL, ft_ray_loop, &game_object_cpy[i]);
	}
	while (i--)
		pthread_join(thread[i], NULL);
	// return (0);
}
