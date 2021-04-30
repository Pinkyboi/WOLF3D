/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/30 23:04:43 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	check_if_number(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
		if (!ft_isdigit(string[i]))
			error_print("wrong argument for number in: ", string);
}

int  parse_counters(char *counter, int min, int max)
{
	check_if_number(counter);
	return (ft_clip_min_max(min, max, ft_atoi(counter)));
}

t_coor  parse_coordinate(char *tuple)
{
	char	**tuple_values;
	t_coor	coordinate;
	short	i;

	tuple_values = parse_block_tuple(tuple);
	i = -1;
	while (tuple_values[++i])
		check_if_number(tuple_values[i]);
	coordinate.x = ft_clip_min(0, ft_atoi(tuple_values[0]));  
	coordinate.y = ft_clip_min(0, ft_atoi(tuple_values[1]));
	return (coordinate);
}