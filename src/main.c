/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/25 22:23:13 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	print_map(t_game_object game_object)
{
	int				i;
	int				j;


	i = -1;
	while (++i < game_object.map.map_dimentions.y)
	{
		j = -1;
		while (++j < game_object.map.map_dimentions.x)
		{
			if (game_object.map.map_grid[i][j].wall)
				printf("%c ", game_object.map.map_grid[i][j].wall->block_icon);
			else
				printf("%c ", '0');
		}
		printf("\n");
	}
}



void		ft_put_pixel(t_game_object *game_object, t_coor position,int color)
{
	t_coor resolution;

	resolution = game_object->render_data.window_resolution;
	if (position.x >= 0 && position.x < resolution.x &&
		position.y >= 0 && position.y < resolution.y)
		game_object->render_data.mlx.mlx_img.img_data[
			(int)(position.y * resolution.x + position.x)] = color;
}

void		ft_draw_hard_line(int start, int end, int color, t_game_object *game_object)
{
	start = ft_clip_min_max(0, game_object->render_data.window_resolution.y, start);
	end = ft_clip_min_max(0, game_object->render_data.window_resolution.y, end);
	while(++start < end)
	{
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x ,start}, color);
	}	
}

void		ft_basic_render(t_game_object *game_object)
{
	if (game_object->ray_data.hit_type == 'H')
		if(game_object->ray_data.current_ray.y > 0)
			game_object->render_data.south_wall.render_function(game_object,
				game_object->render_data.south_wall.render_data);
		else
			game_object->render_data.north_wall.render_function(game_object,
				game_object->render_data.north_wall.render_data);
	else
		if (game_object->ray_data.current_ray.x > 0)
			game_object->render_data.east_wall.render_function(game_object,
				game_object->render_data.east_wall.render_data);
		else
			game_object->render_data.west_wall.render_function(game_object,
				game_object->render_data.west_wall.render_data);
}

short	block_solid(t_game_object *game_object, t_coor grid_position)
{
	t_render_tools render_tool;

	if (grid_position.x < 0 || grid_position.y <= 0)
		return (1);
	if (grid_position.x > game_object->map.map_dimentions.x
		|| grid_position.y > game_object->map.map_dimentions.y)
		return (1);
	if (game_object->map.map_grid[grid_position.y][grid_position.x].wall)
		return (1);
	return (0);
}


int 		ft_check_walls(t_game_object *game_object, int key)
{
	t_d_coor world_position;
	t_d_coor edge;
	t_coor 	grid_position;

	world_position = game_object->player.world_position;
	if(key == FOREWORD)
		world_position = (t_d_coor){world_position.x +
			game_object->player.movement.x,
			world_position.y + game_object->player.movement.y};
	if(key == BACKWARD)
		world_position = (t_d_coor){world_position.x -
			game_object->player.movement.x,
			world_position.y - game_object->player.movement.y};
	edge = ft_add_vector2D(world_position,
		ft_scale_vector2D(ft_normalise_vector2D(game_object->player.movement), 0.5));
	grid_position = (t_coor){world_position.x ,world_position.y};
	if(!block_solid(game_object, (t_coor){edge.x, edge.y}))
	{
		game_object->player.world_position = world_position;
		game_object->player.grid_position = grid_position;
		return (1);
	}
	return(0);
}

int			ft_get_textureX_coor(t_game_object *game_object, t_texture texture)
{
	double wall_index;

	t_d_coor end = ft_add_vector2D(game_object->player.world_position,
		ft_scale_vector2D(game_object->ray_data.current_ray,
			game_object->ray_data.hit_distance));
	wall_index = (game_object->ray_data.hit_type == 'V') ? end.y : end.x;
	wall_index -= (int)wall_index;
	int texture_index = wall_index * (double)texture.texture_width;
	return(texture_index);
}

void		texture_wall(t_game_object *game_object, t_render data)
{
	int 	wall_size;
	int 	start;
	int 	end;
	t_coor	step;
	int		i;
	int 	color;

	i = 0;
	wall_size = (int)(game_object->render_data.view_data.view_plane_distance *
			BLOCK_SIZE / game_object->ray_data.straight_distance);
	start =  (game_object->render_data.view_data.half_view_plane - wall_size / 2) - 1;
	end  = start + wall_size;
	step.y = data.texture.texture_height / wall_size;
	step.x = ft_get_textureX_coor(game_object, data.texture) % BLOCK_SIZE;
	while(++start < end)
	{
		color = ft_scale_color_int(data.texture.texture_data[(int)((int)i *
				data.texture.texture_width + (int)(step.x))], 1);
		ft_put_pixel(game_object,
			(t_coor){game_object->drawing_index.x ,start}, color);
		i += step.y;
	}
}

void		color_wall(t_game_object *game_object, t_render data)
{
	int 	wall_size;
	int 	start;
	int 	end;

	wall_size = (int)(game_object->render_data.view_data.view_plane_distance *
			BLOCK_SIZE / game_object->ray_data.straight_distance);
	start =  (game_object->render_data.view_data.half_view_plane - wall_size / 2) - 1;
	end  = start + wall_size;
	ft_draw_hard_line(start, end, data.color, game_object);
}

void		ft_ray_shooter(t_game_object *game_object)
{
	double	step;
	double	first_angle;
	t_render render_data;

	step = PLAYER_FOV / game_object->render_data.window_resolution.x;
	first_angle = game_object->player.orientation - (PLAYER_FOV / 2);
	game_object->drawing_index.x = -1;
	while(++game_object->drawing_index.x < game_object->render_data.window_resolution.x)
	{
		game_object->ray_data.hit_distance = 0;
		game_object->current_block = NULL;
		first_angle = ft_check_angle(first_angle);
		game_object->ray_data.current_ray = ft_angleToVector2D(first_angle);
		ft_define_check_step(game_object);
		render_data = game_object->current_block->render.render_data;
		game_object->ray_data.straight_distance = game_object->ray_data.hit_distance *
			(double)BLOCK_SIZE * cos(game_object->player.orientation - first_angle);
		if(game_object->current_block)
			game_object->current_block->render.render_function(game_object, render_data);
		// else
			// ft_basic_render(game_object);
		first_angle += step;
	}
}


void		ft_init_win(t_game_object *game_object)
{
	t_mlx mlx;
	t_coor resolution;

	resolution = game_object->render_data.window_resolution;
	mlx.mlx_ptr = mlx_init();
	mlx.mlx_img.img_ptr = mlx_new_image(mlx.mlx_ptr,
			resolution.x, resolution.x);
	mlx.mlx_img.img_data = (int*)mlx_get_data_addr(mlx.mlx_img.img_ptr,
			&mlx.mlx_img.bpp, &mlx.mlx_img.size_l, &mlx.mlx_img.endian);
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, resolution.x,
		resolution.y, "WOLF3D");
	game_object->render_data.mlx = mlx;
	ft_ray_shooter(game_object);
	mlx_put_image_to_window(mlx.mlx_ptr,
			mlx.mlx_win, mlx.mlx_img.img_ptr, 0, 0);
	mlx_hook(mlx.mlx_win, 2, 0, &ft_key_stroke, game_object);
	mlx_hook(mlx.mlx_win, 17, 1, (*ft_exit), game_object);
	mlx_loop(game_object->render_data.mlx.mlx_ptr);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_game_object	*game_object;
	char			*data;

	game_object = malloc(sizeof(t_game_object));
	game_object->parser.block_list = push_block(NULL,
			create_block_node('w', FILLER_ICON,
				(t_render){.color = FILLER_COLOR}, &color_wall));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || argc != 2)
		exit(-1);
	data = read_file(fd);

	load_game_elements(data, game_object);
	if(is_block_solid(game_object, game_object->player.grid_position))
		error_print("FATAL ERROR : ", "the player is on a block or out of the map boundaries");
	ft_init_win(game_object);
	return (0);
}
