/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <abenaiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:52:05 by abenaiss          #+#    #+#             */
/*   Updated: 2021/04/15 03:04:28 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int     isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void    check_if_number(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
		if (!ft_isdigit(string[i]))
			error_print("wrong argument for number in: ", string);
}

void    check_if_alpha(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
		if (!ft_isdigit(string[i]))
			error_print("wrong literal argument in: ", string);
}