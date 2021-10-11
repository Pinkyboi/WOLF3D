/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:23:11 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/26 15:23:12 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	color_sky(t_game_object *game_object, t_render data)
{
	int	i;
	int	j;

	i = game_object->drawing_index.x - 1;
	while (++i <= game_object->drawing_width_end)
	{
		j = -1;
		while (++j < game_object->render_data.view_data.half_view_plane)
			ft_put_pixel(game_object,
				(t_coor){i, j}, data.color);
	}
}

void	texture_sky(t_game_object *game_object, t_render data)
{
	int			color;
	t_coor		step;
	t_d_coor	texture_index;
	double		current_angle;

	step.x = game_object->drawing_index.x - 1;
	current_angle = game_object->player.orientation - (PLAYER_FOV / 2);
	current_angle += PLAYER_FOV / game_object->render_data.window_resolution.x
		* game_object->drawing_index.x;
	while (++step.x <= game_object->drawing_width_end)
	{
		step.y = game_object->render_data.view_data.half_view_plane + 1;
		texture_index.y = data.texture.texture_height;
		while (--step.y >= 0)
		{
			color = data.texture.texture_data[(int)((int)texture_index.y
					* data.texture.texture_width + (int)(texture_index.x))];
			ft_put_pixel(game_object, step, color);
			texture_index.y -= game_object->render_data.skybox.texture_step;
		}
		current_angle += game_object->render_data.skybox.win_per_rad;
		texture_index.x = game_object->render_data.skybox.tex_per_rad
			* ft_check_angle(current_angle);
	}
}

void	ft_get_skybox_infos(t_game_object *game_object,
	t_render_tools	render_tools)
{
	double	plane_distance;
	double	half_view_distance;
	t_view	view;

	view = game_object->render_data.view_data;
	plane_distance = game_object->render_data.view_data.view_plane_distance;
	half_view_distance
		= game_object->render_data.view_data.half_view_plane_save;
	game_object->render_data.skybox.texture_step
		= ((double)render_tools.render_data.texture.texture_height)
		/ ((tan(M_1_PI) * view.view_plane_distance)
			+ view.half_view_plane_save);
	game_object->render_data.skybox.tex_per_rad
		= (double)render_tools.render_data.texture.texture_width / PI_2;
	game_object->render_data.skybox.win_per_rad = (double)PLAYER_FOV
		/ (double)game_object->render_data.window_resolution.x;
}

t_render_tools	ft_parse_sky_render(char *render_argument,
	t_game_object *game_object)
{
	t_render_tools	render_tools;

	if (ft_stock_hex(render_argument, &render_tools.render_data.color))
		render_tools.render_function = &color_sky;
	else if (ft_load_texture(render_argument,
			&render_tools.render_data.texture))
	{
		ft_get_skybox_infos(game_object, render_tools);
		render_tools.render_function = &texture_sky;
	}
	return (render_tools);
}
