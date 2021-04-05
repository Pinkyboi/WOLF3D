/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:10:55 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/05 13:10:58 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double			ft_ray_size(t_wolf *wolf, t_d_coor ray_intersection, double angle)
{
	return((ray_intersection.x - wolf->player.position.x) * cos(angle) +
		(ray_intersection.y - wolf->player.position.y) * sin(angle));
}

t_d_coor		ft_add_vector2D(t_d_coor vector2D, t_d_coor second_vector2D)
{
	vector2D.x += second_vector2D.x;
	vector2D.y += second_vector2D.y;
	return(vector2D);
}

t_d_coor		ft_sub_vector2D(t_d_coor vector2D, t_d_coor second_vector2D)
{
	vector2D.x -= second_vector2D.x;
	vector2D.y -= second_vector2D.y;
	return(vector2D);
}

t_d_coor		ft_scale_vector2D(t_d_coor vector2D, double scale)
{
	vector2D.x *= scale;
	vector2D.y *= scale;
	return(vector2D);
}

t_d_coor	ft_normalise_vector2D(t_d_coor vector){
	double norm;

    norm = sqrtf(FT_SQR(vector.x) + FT_SQR(vector.y));
	vector.x /= norm;
	vector.y /= norm;
	return(vector);
}