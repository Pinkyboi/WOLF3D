/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:53:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/05/02 13:53:06 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_clip_min(int min, double value)
{
	if (value >= min)
		return (value);
	return (min);
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
