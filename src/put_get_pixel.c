/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_get_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:52:52 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/10 09:59:39 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_put_pixel(t_game_object *game_object, t_coor position, int color)
{
	t_coor	resolution;

	resolution = game_object->render_data.window_resolution;
	if (position.x >= 0 && position.x < resolution.x
		&& position.y >= 0 && position.y < resolution.y)
		game_object->render_data.mlx.mlx_img.img_data[
			(int)(position.y * resolution.x + position.x)] = color;
}

int	ft_get_pixel(t_texture *texture, t_coor position)
{
	int	color;

	color = 0;
	if (position.x >= 0 && position.x < texture->texture_width
		&& position.y >= 0 && position.y < texture->texture_height)
		color = texture->texture_data[
			(int)(position.y * texture->texture_width + position.x)];
	return (color);
}
