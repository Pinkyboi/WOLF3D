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

double	ft_check_angle(double angle)
{
	if (angle < 0)
		return (angle + PI_2);
	if (angle > PI_2)
		return (angle - PI_2);
	return (angle);
}

t_d_coor	ft_angleToVector2D(double alpha)
{
	return (ft_normalise_vector2D((t_d_coor){cos(alpha), sin(alpha)}));
}
