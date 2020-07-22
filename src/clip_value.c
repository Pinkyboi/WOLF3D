/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2020/07/10 03:05:22 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		ft_clip_min(int min, double value)
{
	return ((value >= min) ? value : min);
}

double		ft_clip_max(int max, double value)
{
	return ((value <= max) ? value : max);
}

double		ft_clip_min_max(int min, int max, double value)
{
	return (ft_clip_max(max, ft_clip_min(min, value)));
}