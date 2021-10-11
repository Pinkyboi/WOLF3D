/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:13:56 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/03 17:14:02 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	ft_sqr(double number)
{
	return (number * number);
}

double	ft_degree_to_rad(double number)
{
	return ((number * M_PI) / 180);
}

double	ft_check_angle(double angle)
{
	if (angle < 0)
		return (angle + PI_2);
	if (angle > PI_2)
		return (angle - PI_2);
	return (angle);
}

t_d_coor	ft_angle_to_2d_vector(double alpha)
{
	return (ft_normalise_vector_2d((t_d_coor){cos(alpha), sin(alpha)}));
}

double	ft_size_vector_2d(t_d_coor vector2D)
{
	return (sqrt(ft_sqr(vector2D.x) + ft_sqr(vector2D.y)));
}
