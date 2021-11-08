/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:53:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/11/08 18:37:17 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	ft_clip_min(int min, double value)
{
	if (value >= min)
		return (value);
	return (min);
}

double	ft_clip_min_d(double min, double value)
{
	if (value >= min)
		return (value);
	return (min);
}

double	ft_clip_max_d(double max, double value)
{
	if (value <= max)
		return (value);
	return (max);
}

double	ft_clip_max(int max, double value)
{
	if (value <= max)
		return (value);
	return (max);
}

double	ft_clip_min_max(int min, int max, double value)
{
	return (ft_clip_max(max, ft_clip_min(min, value)));
}
