/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenaiss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 21:10:21 by abenaiss          #+#    #+#             */
/*   Updated: 2018/10/07 12:01:33 by abenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	number;
	int			i;

	i = 0;
	number = 0;
	if ((str[0] >= 9 && str[0] <= 13) || str[0] == ' ')
		return (ft_atoi(++str));
	if (str[0] == '-' && str[1] >= '0' && str[1] <= '9')
	{
		number = ft_atoi(++str);
		return (number * -1);
	}
	if (str[0] == '+' && str[1] >= '0' && str[1] <= '9')
		number = ft_atoi(++str);
	else if (str[0] != '-')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			number = (number * 10) + (str[i] - '0');
			++i;
		}
	}
	return ((int)number);
}
