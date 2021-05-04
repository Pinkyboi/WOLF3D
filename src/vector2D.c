/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:10:38 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/03 15:10:39 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	ft_ray_size(t_game_object *gamet_game_object,
	t_d_coor ray_intersection, double angle)
{
	t_d_coor	component;

	component.x = (ray_intersection.x
			- gamet_game_object->player.world_position.x) * cos(angle);
	component.y = (ray_intersection.y
			- gamet_game_object->player.world_position.y) * sin(angle);
	return (component.x + component.y);
}

t_d_coor	ft_add_vector2D(t_d_coor vector2D, t_d_coor second_vector2D)
{
	vector2D.x += second_vector2D.x;
	vector2D.y += second_vector2D.y;
	return (vector2D);
}

t_d_coor	ft_sub_vector2D(t_d_coor vector2D, t_d_coor second_vector2D)
{
	vector2D.x -= second_vector2D.x;
	vector2D.y -= second_vector2D.y;
	return (vector2D);
}

t_d_coor	ft_scale_vector2D(t_d_coor vector2D, double scale)
{
	vector2D.x *= scale;
	vector2D.y *= scale;
	return (vector2D);
}

t_d_coor	ft_normalise_vector2D(t_d_coor vector)
{
	double	norm;

	norm = sqrtf(FT_SQR(vector.x) + FT_SQR(vector.y));
	vector.x /= norm;
	vector.y /= norm;
	return (vector);
}
