/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/15 01:33:14 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_hex_to_int(char *number)
{
	int	rank;
	int	final_number;
	int	i;
	int	j;

	rank = ft_strlen(number) - 1;
	final_number = 0;
	i = -1;
	while (number[++i])
	{
		j = 0;
		if (!ft_strchr(HEX_FILTER, ft_tolower(number[i])))
			return (-1);
		while (j < 16 && ft_tolower(number[i]) != HEX_FILTER[j])
			j++;
		final_number += j * pow(16, rank);
		rank--;
	}
	return (final_number);
}

int	ft_hex_to_color(char *color)
{
	int	i;

	i = -1;
	while (color[++i])
	{
		if (i >= 6 || !ft_strchr(HEX_FILTER, ft_tolower(color[i])))
			ft_err_print("wrong color format in:", color);
	}
	return (ft_hex_to_int(color));
}

int	ft_stock_hex(char *color, int *color_stock)
{
	int	color_len;

	color_len = ft_strlen(color);
	if (color_len > 1 && color[0] == '#')
	{
		*color_stock = ft_hex_to_color(&color[1]);
		return (1);
	}
	return (0);
}
