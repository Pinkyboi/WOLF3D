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

#define NEON_EDGE_COLOR 0xccffbd
#define NEON_INNER_COLOR 0x40394a
#define NEON_VOID_COLOR 0

int	get_neon_tile_position(t_game_object *game_object,
		t_d_coor tile_arg,double shade)
{
	t_d_coor		texture_ratio;
	t_coor			tile_coor;
	t_block_list	*block;

	texture_ratio.y = game_object->player.world_position.y
		+ (T_DISTANCE * sin(T_ANGLE));
	texture_ratio.x = game_object->player.world_position.x
		+ (T_DISTANCE * cos(T_ANGLE));
	tile_coor = (t_coor){(int)texture_ratio.x, (int)texture_ratio.y};
	texture_ratio.x -= tile_coor.x;
	texture_ratio.y -= tile_coor.y;
	if((texture_ratio.x >= 0 && texture_ratio.x <= 0.02) ||
		(texture_ratio.x >= 0.98 && texture_ratio.x <= 1))
		return (NEON_EDGE_COLOR);
	if((texture_ratio.y >= 0 && texture_ratio.y <= 0.02) ||
		(texture_ratio.y >= 0.98 && texture_ratio.y <= 1))
		return (NEON_EDGE_COLOR);
	if((texture_ratio.x >= 0.25 - 0.002 && texture_ratio.x <= 0.25 + 0.002) || (texture_ratio.x >= 0.5 - 0.002 && texture_ratio.x <= 0.5 + 0.002) || (texture_ratio.x >= 0.75 - 0.002 && texture_ratio.x <= 0.75 + 0.002))
		return (NEON_INNER_COLOR);
	if((texture_ratio.y >= 0.25 - 0.002 && texture_ratio.y <= 0.25 + 0.002) || (texture_ratio.y >= 0.5 - 0.002 && texture_ratio.y <= 0.5 + 0.002) || (texture_ratio.y >= 0.75 - 0.002 && texture_ratio.y <= 0.75 + 0.002))
		return (NEON_INNER_COLOR);
	return(NEON_VOID_COLOR);
}
void	tile_neon(t_game_object *game_object, t_coor range)
{
	double	wall_ratio;
	double	angle;
	double	distance;
	double	shade;
	int		color;

	while (range.x <= range.y)
	{
		wall_ratio = abs(range.x
				- game_object->render_data.view_data.half_view_plane);
		angle = game_object->ray_data.angle;
		distance = game_object->player.height / wall_ratio
			* game_object->render_data.view_data.view_plane_distance
			/ cos(game_object->player.orientation - angle) / (double)BLOCK_SIZE;
		shade = 1;
		if (game_object->player.view_distance > 0)
			shade = ft_clip_min_max(0, 1, game_object->player.view_distance
					/ (distance * (double)BLOCK_SIZE));
		color = get_neon_tile_position(game_object,
				(t_d_coor){distance, angle},shade);
		color = ft_scale_color_int(color, 0.7);
		color = ft_scale_color_int(color, shade);
		if (color != -1)
			ft_put_pixel(game_object,
				(t_coor){game_object->drawing_index.x, range.x}, color);
		range.x++;
	}
}


int	ft_neon_x_color(t_game_object *game_object, double y_index)
{
	double		wall_index;
	t_d_coor	end;
	
	end = ft_add_vector2D(game_object->player.world_position,
			ft_scale_vector2D(game_object->ray_data.current_ray,
				game_object->ray_data.hit_distance));
	wall_index = end.x;
	if (game_object->ray_data.hit_type == 'V')
		wall_index = end.y;
	wall_index -= (int)wall_index;
	if((wall_index >= 0 && wall_index <= 0.02) || (wall_index >= 0.98 && wall_index <= 1))
		return (NEON_EDGE_COLOR);
	if((wall_index >= 0.25 - 0.002 && wall_index <= 0.25 + 0.002) || (wall_index >= 0.5 - 0.005 && wall_index <= 0.5 + 0.005) || (wall_index >= 0.75 - 0.005 && wall_index <= 0.75 + 0.005))
		return (NEON_INNER_COLOR);
	if((y_index >= 0.25 - 0.002 && y_index <= 0.25 + 0.002) || (y_index >= 0.5 - 0.005 && y_index <= 0.5 + 0.005) || (y_index >= 0.75 - 0.005 && y_index <= 0.75 + 0.005))
		return (NEON_INNER_COLOR);
	return(NEON_VOID_COLOR);
}

void	ft_draw_neon_line(t_coor edges,
	t_game_object *game_object, double shade, double wall_size)
{
	t_d_coor	step;
	double		texture_index;
	int			color;

	texture_index = 0;
	step.y = 1.0 / (edges.y - edges.x + 1);
	while (edges.x <= edges.y)
	{
		color = ft_neon_x_color(game_object, texture_index);
		color = ft_scale_color_int(color, shade);
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x, edges.x}, color);
		edges.x++;
		texture_index += step.y;
	}
}


void	ft_neon_texture(t_game_object *game_object)
{
	int		start;
	int		end;
	double	wall_size;
	double	shade;

	wall_size = (int)(game_object->render_data.view_data.view_plane_distance
			* BLOCK_SIZE / game_object->ray_data.straight_distance);
	start = game_object->render_data.view_data.half_view_plane
		- (wall_size / 2);
	end = start + wall_size;
	shade = 1;
	if (game_object->ray_data.hit_type == 'V')
		shade = 0.8;
	if (game_object->player.view_distance > 0)
		shade = ft_clip_min_max(0, 1, game_object->player.view_distance
				/ game_object->ray_data.straight_distance);
	ft_draw_neon_line((t_coor){start, end},
		game_object, shade, wall_size);
	tile_neon(game_object, (t_coor){0, start});
	tile_neon(game_object, (t_coor){end,
		game_object->render_data.window_resolution.y});
}

void	ft_neon_render(t_game_object *game_object)
{
	t_render		render_data;
	t_block_list	*current_block;

	current_block = game_object->current_block;
	if (game_object->current_block)
	{
		ft_neon_texture(game_object);
	}
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

void	ft_ray_shooter(t_game_object *game_object)
{
	double		step;
	double		first_angle;
	t_render	render_data;

	step = PLAYER_FOV / game_object->render_data.window_resolution.x;
	first_angle = game_object->player.orientation - (PLAYER_FOV / 2);
	game_object->drawing_index.x = -1;
	game_object->render_data.skybox.sky.render_function(game_object,
		game_object->render_data.skybox.sky.render_data);
	while (++game_object->drawing_index.x
		< game_object->render_data.window_resolution.x)
	{
		game_object->ray_data.hit_distance = 0;
		game_object->current_block = NULL;
		first_angle = ft_check_angle(first_angle);
		game_object->ray_data.current_ray = ft_angleToVector2D(first_angle);
		ft_get_wall_distance(game_object, first_angle);
		game_object->render_data.render_function(game_object);
		first_angle += step;
	}
}
