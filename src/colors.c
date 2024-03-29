/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 21:51:36 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/03 14:48:03 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_rgb_to_int(t_color color)
{
	int	c;
	int	g;
	int	b;

	g = ft_clip_min_max(0, 255, color.g * 255);
	b = ft_clip_min_max(0, 255, color.b * 255);
	c = ft_clip_min_max(0, 255, color.r * 255);
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (ft_clip_min(0, c));
}

t_color	ft_scale_color(t_color color, double scalar)
{
	return ((t_color){color.r * scalar, color.g * scalar, color.b * scalar});
}

t_color	ft_add_colors(t_color first, t_color second)
{
	t_color	result;

	result.r = first.r + second.r;
	result.g = first.g + second.g;
	result.b = first.b + second.b;
	return (result);
}

int	ft_scale_color_int(int color, double scalar)
{
	t_color	scaled_color;
	int		c;
	int		g;
	int		b;

	scaled_color = ft_scale_color(ft_int_to_rgb(color), scalar);
	g = ft_clip_min_max(0, 255, scaled_color.g);
	b = ft_clip_min_max(0, 255, scaled_color.b);
	c = ft_clip_min_max(0, 255, scaled_color.r);
	c = (c << 8) | g;
	c = (c << 8) | b;
	return (c);
}

t_color	ft_int_to_rgb(int color)
{
	t_color	rgb;

	rgb.r = (color & 0xFF0000) >> 16;
	rgb.g = (color & 0xFF00) >> 8;
	rgb.b = color & 0xFF;
	return (rgb);
}
