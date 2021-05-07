/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/07 22:40:44 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void	ft_ray_shooter(t_game_object *game_object)
{
	double		step;
	double		first_angle;
	t_render	render_data;

	step = PLAYER_FOV / game_object->render_data.window_resolution.x;
	first_angle = game_object->player.orientation - (PLAYER_FOV / 2);
	game_object->drawing_index.x = -1;
	while (++game_object->drawing_index.x
		< game_object->render_data.window_resolution.x)
	{
		game_object->ray_data.hit_distance = 0;
		game_object->current_block = NULL;
		first_angle = ft_check_angle(first_angle);
		game_object->ray_data.current_ray = ft_angleToVector2D(first_angle);
		ft_define_check_step(game_object);
		game_object->ray_data.straight_distance
			= game_object->ray_data.hit_distance;
		game_object->ray_data.straight_distance *= (double)BLOCK_SIZE;
		game_object->ray_data.straight_distance
			*= cos(game_object->player.orientation - first_angle);
    game_object->ray_data.angle = first_angle;
		game_object->render_data.render_function(game_object);
		first_angle += step;
	}
}

t_block_list *get_floor_ceiling(t_coor tile_coor, t_game_object *game_object, char type)
{
	t_block_list	*render_tool;

	render_tool = NULL;
	if(!is_block_solid(game_object,tile_coor))
	{
		if(type == 'C')
		{
			if(game_object->map.map_grid[tile_coor.y][tile_coor.x].ceiling)
				render_tool = game_object->map.map_grid[tile_coor.y]
				[tile_coor.x].ceiling;
		}
		else if(game_object->map.map_grid[tile_coor.y] [tile_coor.x].floor)
		{
			render_tool = game_object->map.map_grid[tile_coor.y]
			[tile_coor.x].floor;
		}
	}
	return (render_tool);
}

int	texture_pixel(t_game_object *game_object, t_render data)
{
	int		color;
	t_d_coor 	coordinates;
	
	coordinates = data.texture.coordinates;
	color = data.texture.texture_data[(int)((int)coordinates.y
			* data.texture.texture_width + (int)(coordinates.x))];
	color = ft_scale_color_int(color, 0.7);
	return (color);
}
int	color_pixel(t_game_object *game_object, t_render data)
{
	int color;

	return (ft_scale_color_int(data.color, 0.7));
}

int	get_tile_position(t_game_object *game_object, double distance, double angle, char type)
{
	t_d_coor texture_ratio;
	t_coor	tile_coor;
	t_block_list *block;

	texture_ratio.y = game_object->player.world_position.y + (distance * sin(angle));
	texture_ratio.x = game_object->player.world_position.x + (distance * cos(angle));
	tile_coor = (t_coor){(int)texture_ratio.x ,(int)texture_ratio.y};
    
    block = get_floor_ceiling(tile_coor,game_object,type);
	if(block)
	{
        if(block->render.render_function == &texture_wall)
		{
			texture_ratio.x -= tile_coor.x;
			texture_ratio.y -= tile_coor.y;
			texture_ratio.x *= block->render.render_data.texture.texture_width;
			texture_ratio.y *= block->render.render_data.texture.texture_height;
			block->render.render_data.texture.coordinates = texture_ratio;
			return (texture_pixel(game_object, block->render.render_data));
		}
		else
			return (color_pixel(game_object, block->render.render_data));
	}
        
	return (-1);
}

void	ft_floor_rand_ceilings(t_game_object *game_object, t_coor range, char type)
{
	double	wall_ratio;
	double	angle;
	double 	distance;
	int		color;

	while(range.x <= range.y)
	{
		wall_ratio = abs(range.x
            - game_object->render_data.view_data.half_view_plane);
		angle = game_object->ray_data.angle;
		distance = game_object->player.height / wall_ratio
        * game_object->render_data.view_data.view_plane_distance
        / cos(game_object->player.orientation - angle) / (double)BLOCK_SIZE;
		color = get_tile_position(game_object,distance,angle,type);
        if (color != -1)
			ft_put_pixel(game_object,
				(t_coor){game_object->drawing_index.x, range.x}, color);
		range.x++;
	}
}